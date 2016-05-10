#include "MainWindow.hpp"
#include "GraphicsView.hpp"

#include <limits>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
	QGraphicsScene *scene = new QGraphicsScene(this);
	scene->addEllipse(0, 0, 64, 64, QPen(), Qt::red);

	GraphicsView *view = new GraphicsView(this);
	view->setScene(scene);
	view->setGridRect(QRect(0, 0, 256, 128));

	setCentralWidget(view);
}
