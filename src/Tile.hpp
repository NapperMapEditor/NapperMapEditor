#ifndef TILE_H
#define TILE_H

#include <QString>
#include <QIcon>
#include <QImage>

class Tile
{
public:
	Tile();
	Tile(const QString &filePath);

	const QIcon &getIcon() const;
	const QImage &getImage() const;
	const QString &getName() const;

	void setName(const QString& name);

private:
	QString name_;
	QIcon icon_;
	QImage image_;

};

#endif // TILE_H
