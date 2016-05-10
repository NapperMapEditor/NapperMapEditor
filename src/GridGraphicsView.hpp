#ifndef GRIDGRAPHICSVIEW_H
#define GRIDGRAPHICSVIEW_H

#include <QGraphicsView>

class GridGraphicsView : public QGraphicsView
{
public:
	GridGraphicsView(QWidget *parent = nullptr);

	QRect gridRect() const;
	void setGridRect(const QRect &rect);

	void viewTranslate(qreal dx, qreal dy);
	void viewScale(qreal sx, qreal sy);

protected:
	virtual void drawBackground(QPainter *painter, const QRectF &rect) override;
	virtual void drawForeground(QPainter *painter, const QRectF &rect) override;

	virtual void resizeEvent(QResizeEvent *event) override;

private:
	QRect gridRect_;
	bool shrinkGrid_;
	bool movedHor_;
	bool movedVer_;
	uint8_t gridSizeHor_;
	uint8_t gridSizeVer_;
	QVector<QLineF> lineHor_;
	QVector<QLineF> lineVer_;
	QPen penAlternating1_;
	QPen penAlternating2_;
	float zoom_;
};

#endif // GRIDGRAPHICSVIEW_H
