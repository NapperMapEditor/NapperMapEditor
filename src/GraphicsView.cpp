#include "GraphicsView.hpp"

#include <QWheelEvent>

GraphicsView::GraphicsView(QWidget *parent) : GridGraphicsView(parent)
{
	QGraphicsView::setDragMode(QGraphicsView::ScrollHandDrag);
}

void GraphicsView::mouseMoveEvent(QMouseEvent *event)
{
	GridGraphicsView::mouseMoveEvent(event);
	viewScale(1, 1); // TODO: Hack to redraw grid.
}

void GraphicsView::wheelEvent(QWheelEvent *event)
{
	// TODO: Make work with more precise mouse wheels.
	viewScale(event->angleDelta().y() > 0 ? 2 : 0.5f, event->angleDelta().y() > 0 ? 2 : 0.5f);
}
