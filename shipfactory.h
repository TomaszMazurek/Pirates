#ifndef SHIPFACTORY_H
#define SHIPFACTORY_H

#include "pirateship.h"
#include "cargoship.h"
#include "brig.h"
#include "barque.h"
#include <QObject>
#include <QPointer>
#include <QGraphicsScene>

struct Course{
    QPoint position;
    qreal angle;
};

class ShipFactory : public QObject
{
    Q_OBJECT

public:
    explicit ShipFactory(QObject *parent = nullptr);
    explicit ShipFactory(QGraphicsScene * _scene, QObject *parent = nullptr);
    ~ShipFactory();
    Course getPosition();
    void setMaxSpeed(double _speed);
    PirateShip *spawnPirateShip();
    void spawnShipTimer(int _shipType, int spawnTime);
    void setShipType(int _shipType){shipType = _shipType;}
    int getShipType(){return shipType;}

private:
    QGraphicsScene * scene;
    PirateShip * pirateShip;
    CargoShip* cargoShip;
    Brig* brig;
    Barque* barque;

    int shipType;
    double maxSpeed;

signals:

public slots:
    void spawnCargoShip();
    void spawnBrig();
    void spawnBarque();

};

#endif // SHIPFACTORY_H
