#include "TileSelectWidget.hpp"

#include <QDir>

TileSelectWidget::TileSelectWidget(QWidget *parent) : QWidget(parent)
{
	gridView_ = true;

	comboBox_ = new TileSetComboBox(this);

	listView_ = new QListView(this);
	listView_->setGridSize(QSize(32,32));
	listView_->setDragEnabled(true);
	listView_->setResizeMode(QListView::Adjust);
	listView_->setViewMode(QListView::IconMode);

	viewModeButton_ = new QPushButton(this);

	buttonLayout_ = new QHBoxLayout(Q_NULLPTR);
	buttonLayout_->addWidget(comboBox_);
	buttonLayout_->addWidget(viewModeButton_);

	mainLayout_ = new QVBoxLayout(this);
	mainLayout_->addLayout(buttonLayout_);
	mainLayout_->addWidget(listView_);

	setLayout(mainLayout_);

	connect(comboBox_, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &TileSelectWidget::selectTileSet);
	connect(viewModeButton_, &QPushButton::pressed, this, &TileSelectWidget::toggleViewMode);
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
			tileSet->setGridMode(true);
		}

		tileSet_.append(tileSet);
	}

	listView_->setModel(tileSet_[0]);
}

void TileSelectWidget::toggleViewMode()
{
	gridView_ = !gridView_;

	for(auto t : tileSet_)
	{
		t->setGridMode(gridView_);
	}

	if (gridView_)
	{
		listView_->setViewMode(QListView::IconMode);
	}
	else
	{
		listView_->setViewMode(QListView::ListMode);
	}
}
