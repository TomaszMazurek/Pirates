#ifndef CARGOSHIP_H
#define CARGOSHIP_H

#include <QObject>
#include "ship.h"
#include "QGraphicsPolygonItem"

class CargoShip : public Ship
{
    Q_OBJECT
public:
    explicit CargoShip(QString _name, double _speed = 3, int _defense = 10, int _scaleFactor = 300, QObject *parent = nullptr);
    ~CargoShip();
};

#endif // CARGOSHIP_H
