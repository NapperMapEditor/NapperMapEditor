#include "TileModel.hpp"

TileModel::TileModel(QObject *parent) : QAbstractListModel(parent)
{
	gridMode_ = true;
}

int TileModel::rowCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent);
	return tiles_.count();
}

QVariant TileModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid() || index.row() >= tiles_.size())
	{
		return QVariant();
	}

	switch(role)
	{
	case Qt::DisplayRole:
	{
		if (gridMode_)
		{
			return "";
		}
		else
		{
			return tiles_[index.row()].getName();
		}
	}

	case Qt::ToolTipRole:
	{
		return tiles_[index.row()].getName();
	}

	case Qt::DecorationRole:
	{
		return tiles_[index.row()].getIcon();
	}

	default:
	{
		return QVariant();
	}
	}
}

Tile TileModel::getTile(const QModelIndex &index)
{
	return tiles_[index.row()];
}


Qt::ItemFlags TileModel::flags(const QModelIndex &index) const
{
	return QAbstractItemModel::flags(index) | Qt::ItemIsDragEnabled;
}


bool TileModel::setData(const QModelIndex &index,
                        const QVariant &value, int role)
{
	return false;
}

bool TileModel::setData(const QModelIndex &index,
                        const Tile &value, int role)
{
	if (index.isValid() && role == Qt::EditRole)
	{
		tiles_[index.row()] = value;
		emit dataChanged(index, index);
		return true;
	}

	return false;
}

bool TileModel::insertRows(int position, int rows, const QModelIndex &parent)
{
	Q_UNUSED(parent);
	beginInsertRows(QModelIndex(), position, position+rows-1);

	for (int row = 0; row < rows; ++row)
	{
		tiles_.insert(position, Tile());
	}

	endInsertRows();
	return true;

}

bool TileModel::removeRows(int position, int rows, const QModelIndex &parent)
{
	Q_UNUSED(parent);
	beginRemoveRows(QModelIndex(), position, position+rows-1);

	for (int row = 0; row < rows; ++row)
	{
		tiles_.removeAt(position);
	}

	endRemoveRows();
	return true;

}

void TileModel::setGridMode(bool mode)
{
	gridMode_ = mode;
}
