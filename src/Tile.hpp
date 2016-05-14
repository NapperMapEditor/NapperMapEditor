#ifndef TILE_H
#define TILE_H

#include <QString>
#include <QIcon>
#include <QPixmap>

class Tile
{
public:
	Tile();
	Tile(const QString &filePath);

	const QIcon &getIcon() const;
	const QPixmap &getImage() const;
	const QString &getName() const;

	void setName(const QString& name);

private:
	QString name_;
	QIcon icon_;
	QPixmap image_;

};

#endif // TILE_H
