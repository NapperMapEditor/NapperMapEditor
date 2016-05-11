#include "TileSelectWidget.hpp"

#include <QDir>

TileSelectWidget::TileSelectWidget(QWidget *parent) : QWidget(parent)
{
	comboBox_ = new TileSetComboBox(this);
	listView_ = new QListView(this);

	layout_ = new QVBoxLayout(this);
	layout_->addWidget(comboBox_);
	layout_->addWidget(listView_);

	connect(comboBox_, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &TileSelectWidget::selectTileSet);
}

void TileSelectWidget::selectTileSet(int set)
{
	if (tileSet_.size() > 0)
	{
		listView_->setModel(tileSet_[set]);
	}
}

void TileSelectWidget::loadDirectory(const QString &path)
{
	QDir rootDir = QDir(path);
	rootDir.setFilter(QDir::Dirs);
	QString fName = path;

	QStringList tileSets = rootDir.entryList();

	for (auto subDir : tileSets)
	{
		if (subDir == "." || subDir == "..")
		{
			continue;
		}

		comboBox_->addItem(subDir);

		TileModel *tileSet = new TileModel(this);

		QDir imgDir = QDir(rootDir.path() + "/" + subDir);
		imgDir.setFilter(QDir::Files);

		QStringList tiles = imgDir.entryList();

		for (auto tile : tiles)
		{
			QString fName = rootDir.path();
			fName += "/" + subDir;
			fName += "/" + tile;

			int row = tileSet->rowCount();
			tileSet->insertRows(row, 1, QModelIndex());
			QModelIndex index = tileSet->index(row, 0, QModelIndex());
			tileSet->setData(index, Tile(fName));
		}

		tileSet_.append(tileSet);
	}

	// TODO: Use custom delegate so can switch to QListView::IconMode
	listView_->setModel(tileSet_[0]);
	listView_->setDragEnabled(true);
}
