#ifndef TILEMODEL_HPP
#define TILEMODEL_HPP

#include "Tile.hpp"

#include <QAbstractListModel>
#include <QList>

class TileModel : public QAbstractListModel
{
public:
	TileModel(QObject *parent);
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	QVariant data(const QModelIndex &index, int role) const;
	Qt::ItemFlags flags(const QModelIndex &index) const;
	bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
	bool setData(const QModelIndex &index, const Tile &value, int role = Qt::EditRole);
	bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex());
	bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex());

private:
	QList<Tile> tiles_;
};

#endif // TILEMODEL_H
