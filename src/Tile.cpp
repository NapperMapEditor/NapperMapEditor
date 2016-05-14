#include "Tile.hpp"

#include <QFileInfo>
#include <QImage>

Tile::Tile()
{
	name_ = "";
	icon_ = QIcon();
	image_ = QPixmap();
}

Tile::Tile(const QString& filePath)
{
	QFileInfo file(filePath);

	name_ = file.baseName();
	icon_ = QIcon(filePath);
	image_ = QPixmap(filePath);
}

const QIcon& Tile::getIcon() const
{
	return icon_;
}

const QPixmap& Tile::getImage() const
{
	return image_;
}

const QString& Tile::getName() const
{
	return name_;
}

void Tile::setName(const QString& name)
{
	name_ = name;
}
