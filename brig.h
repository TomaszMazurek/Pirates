#ifndef BRIG_H
#define BRIG_H

#include <QObject>
#include "ship.h"
#include "QGraphicsPolygonItem"

class Brig: public Ship
{
      Q_OBJECT
public:
    explicit Brig(QString name, double _speed = 4, int _defense = 20, int _scaleFactor = 500, QObject *parent = nullptr);
    ~Brig();
};

#endif // BRIG_H
