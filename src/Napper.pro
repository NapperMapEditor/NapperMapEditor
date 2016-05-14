#-------------------------------------------------
#
# Project created by QtCreator 2016-05-07T16:57:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Grid
TEMPLATE = app


SOURCES +=\
        MainWindow.cpp \
    Main.cpp \
    GridGraphicsView.cpp \
    GraphicsView.cpp \
    MainWidget.cpp \
    Tile.cpp \
    TileModel.cpp \
    TileSelectWidget.cpp \
    TileSetComboBox.cpp

HEADERS  += MainWindow.hpp \
    GridGraphicsView.hpp \
    GraphicsView.hpp \
    MainWidget.hpp \
    Tile.hpp \
    TileModel.hpp \
    TileSelectWidget.hpp \
    TileSetComboBox.hpp

FORMS    +=

DISTFILES += \
    Grid.pro.user
