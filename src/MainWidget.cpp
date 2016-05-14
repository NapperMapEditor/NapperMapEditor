#include "MainWidget.hpp"
#include "GraphicsView.hpp"
#include "TileSelectWidget.hpp"

MainWidget::MainWidget(QWidget *parent) : QSplitter(parent)
{
	QGraphicsScene *scene = new QGraphicsScene(this);
	scene->addEllipse(0, 0, 64, 64, QPen(), Qt::red);

	TileSelectWidget *tileSelector = new TileSelectWidget(this);
	tileSelector->loadDirectory("/usr/share/icons/Adwaita/256x256/");

	GraphicsView *view = new GraphicsView(this);
	view->setScene(scene);
	view->setGridRect(QRect(0, 0, 256, 128));

	addWidget(tileSelector);
	addWidget(view);
}
