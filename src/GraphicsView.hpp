#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include "GridGraphicsView.hpp"

class GraphicsView : public GridGraphicsView
{
public:
	GraphicsView(QWidget *parent = nullptr);

protected:
	virtual void mouseMoveEvent(QMouseEvent *event) override;
	virtual void wheelEvent(QWheelEvent *event) override;
};

#endif // GRAPHICSVIEW_H
