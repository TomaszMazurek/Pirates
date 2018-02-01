#ifndef BARQUE_H
#define BARQUE_H

#include <QObject>
#include "ship.h"
#include "QGraphicsPolygonItem"

class Barque: public Ship
{
      Q_OBJECT
public:
    explicit Barque(QString _name, double _speed = 5, int _defense = 30, int _scaleFactor = 700, QObject *parent = nullptr);
    ~Barque();
};

#endif // BARQUE_H
