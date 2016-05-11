#ifndef TILESELECTWIDGET_H
#define TILESELECTWIDGET_H

#include "TileSetComboBox.hpp"
#include "TileModel.hpp"

#include <QVBoxLayout>
#include <QListView>

class TileSelectWidget : public QWidget
{
public:
	TileSelectWidget(QWidget *parent);
	void loadDirectory(const QString &path);

private:

	void selectTileSet(int set);

	QVBoxLayout *layout_;
	TileSetComboBox *comboBox_;
	QListView *listView_;
	QList<TileModel*> tileSet_;
};

#endif // TILESELECTWIDGET_H
