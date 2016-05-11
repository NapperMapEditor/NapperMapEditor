#ifndef TILESELECTWIDGET_H
#define TILESELECTWIDGET_H

#include "TileSetComboBox.hpp"
#include "TileModel.hpp"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListView>
#include <QPushButton>

class TileSelectWidget : public QWidget
{
public:
	TileSelectWidget(QWidget *parent);
	void loadDirectory(const QString &path);
	void toggleViewMode();

private:

	void selectTileSet(int set);

	QHBoxLayout *buttonLayout_;
	QVBoxLayout *mainLayout_;

	QPushButton *viewModeButton_;
	TileSetComboBox *comboBox_;
	QListView *listView_;

	QList<TileModel*> tileSet_;
	bool gridView_;
};

#endif // TILESELECTWIDGET_H
