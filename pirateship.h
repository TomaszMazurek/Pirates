#ifndef PIRATESHIP_H
#define PIRATESHIP_H

#include "ship.h"
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QObject>

class PirateShip : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    explicit PirateShip(QObject *parent = 0);
    ~PirateShip();
    void setSpeed(double _speed);
    double getSpeed();
    double distanceToTarget(QGraphicsItem *target);
    void rotateToPoint(QPointF p);
    void setAttacked(){Attacked = true;}
    bool hasBeenAttacked(){return Attacked;}
    bool checkBoundries();

private:
    QTimer *timer;
    QGraphicsPolygonItem *proximityArea;
    double speed;
    double theta;
    double dx;
    double dy;
    QPointF targetPos;
    bool hasTarget;
    bool Attacked;
    bool isInBoundries;
    int attack;


signals:
    void targetDestroyed();
    void targetEngaged();
public slots:
    void move();
    void aquireTarget();
};

#endif // PIRATESHIP_H
