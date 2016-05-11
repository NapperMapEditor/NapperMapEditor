#ifndef TILESETCOMBOBOX_H
#define TILESETCOMBOBOX_H

#include <QComboBox>

class TileSetComboBox : public QComboBox
{
	Q_OBJECT

public:
	TileSetComboBox(QWidget *parent);

signals:
	void currentIndexChanged(int index);
};

#endif // TILESETCOMBOBOX_H
