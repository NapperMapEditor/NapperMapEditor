#include "MainWindow.hpp"
#include "MainWidget.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
	MainWidget *widget = new MainWidget(this);
	setCentralWidget(widget);
}
