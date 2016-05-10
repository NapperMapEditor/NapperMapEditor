#include "GridGraphicsView.hpp"

#include <QVector>
#include <QDebug>

#include <cmath>
#include <algorithm>

GridGraphicsView::GridGraphicsView(QWidget *parent)
	: QGraphicsView(parent)
	, shrinkGrid_(false)
	, movedHor_(true)
	, movedVer_(true)
	, gridSizeHor_(16)
	, gridSizeVer_(16)
	, penAlternating1_(Qt::black, 0, Qt::DashLine, Qt::FlatCap)
	, penAlternating2_(Qt::white, 0, Qt::DashLine, Qt::FlatCap)
	, zoom_(1)
{
	setSceneRect(INT_MIN / 2, INT_MIN / 2, INT_MAX, INT_MAX);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	QVector<qreal> dashPattern({4, 4});
	penAlternating1_.setDashPattern(dashPattern);
	penAlternating2_.setDashOffset(4);
	penAlternating2_.setDashPattern(dashPattern);

	// TODO: This is a temporary fix for line offset messing up when updating partial.
	setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
}

QRect GridGraphicsView::gridRect() const
{
	return gridRect_;
}

void GridGraphicsView::setGridRect(const QRect &rect)
{
	gridRect_ = rect;
	movedHor_ = true;
	movedVer_ = true;
}

void GridGraphicsView::viewTranslate(qreal dx, qreal dy)
{
	translate(dx, dy);
	movedHor_ = (dx != 0);
	movedVer_ = (dy != 0);
}

void GridGraphicsView::viewScale(qreal sx, qreal sy)
{
	scale(sx, sy);
	movedHor_ = true;
	movedVer_ = true;
	shrinkGrid_ = true;
	zoom_ *= sx;
}

void GridGraphicsView::drawBackground(QPainter *painter, const QRectF &)
{
	QPixmap pixmap(12, 12);
	QPainter pixmapPainter(&pixmap);
	pixmapPainter.setPen(Qt::transparent);
	pixmapPainter.setBrush(Qt::gray);
	pixmapPainter.drawRect(0, 0, 12, 12);
	pixmapPainter.setBrush(Qt::white);
	pixmapPainter.drawRect(0, 0, 6, 6);
	pixmapPainter.drawRect(6, 6, 6, 6);
	painter->drawTiledPixmap(sceneRect(), pixmap);
	painter->setPen(Qt::transparent);
	painter->setBrush(Qt::gray);
	painter->drawRect(gridRect_);
}

void GridGraphicsView::drawForeground(QPainter *painter, const QRectF &rect)
{
	qreal maxY = std::min<qreal>(gridRect_.height(), rect.bottom());
	qreal maxX = std::min<qreal>(gridRect_.width(), rect.right());

	if (movedHor_)
	{
		// Clear without decreasing allocated capacity.
		lineHor_.erase(lineHor_.begin(), lineHor_.end());

		int64_t topScreen = static_cast<int64_t>(round(rect.top()));
		int64_t topOffset = topScreen % gridSizeHor_;

		for (int64_t y = std::max<int64_t>(0, topScreen - topOffset); y <= maxY; y += gridSizeHor_)
		{
			lineHor_.append(QLine(0, y, gridRect_.width(), y));
		}

		movedHor_ = false;
	}

	if (movedVer_)
	{
		// Clear without decreasing allocated capacity.
		lineVer_.erase(lineVer_.begin(), lineVer_.end());

		int64_t leftScreen = static_cast<int64_t>(round(rect.left()));
		int64_t leftOffset = leftScreen % gridSizeVer_;

		for (qreal x = std::max<int64_t>(0, leftScreen - leftOffset); x <= maxX; x += gridSizeVer_)
		{
			lineVer_.append(QLineF(x, 0, x, gridRect_.height()));
		}

		movedVer_ = false;
	}

	// Prevent having unclaimable memory.
	if (shrinkGrid_)
	{
		lineHor_.squeeze();
		lineVer_.squeeze();
		shrinkGrid_ = false;
	}


	for (const auto &line : lineHor_)
	{
		painter->setPen(penAlternating1_);
		painter->drawLine(line);
		painter->setPen(penAlternating2_);
		painter->drawLine(line);
	}
	for (const auto &line : lineVer_)
	{
		painter->setPen(penAlternating1_);
		painter->drawLine(line);
		painter->setPen(penAlternating2_);
		painter->drawLine(line);
	}
}

void GridGraphicsView::resizeEvent(QResizeEvent *event)
{
	QGraphicsView::resizeEvent(event);
	movedHor_ = true;
	movedVer_ = true;
}
