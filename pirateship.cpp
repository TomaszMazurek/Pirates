#include "pirateship.h"
#include "game.h"
#include <QDebug>
#include <QList>
#include <QtMath>
#include <QLineF>
#include <QPolygonF>
#include <QVector>

PirateShip::PirateShip(QObject *parent) : QObject(parent),
    speed(5), hasTarget(false), attack(100), Attacked(false), isInBoundries(true)
{
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(40);

    //utworzenie wektora współrzędnych dla poligonu
    QVector<QPointF> proximityVector;
    proximityVector << QPoint(1,0) << QPoint(2,0) << QPoint(3,1) << QPoint(3,2)<< QPoint(2,3)
              << QPoint(1,3) << QPoint(0,2) << QPoint(0,1);

    //skalowanie obszaru zbliżenia
    int SCALE_FACTOR = 1000;
    for(int i = 0, n = proximityVector.size(); i < n; ++i){
        proximityVector[i] *= SCALE_FACTOR;
    }

    //utworzenie poligonu dla obszaru zbliżenia
    QPolygonF polygon(proximityVector);
    proximityArea = new QGraphicsPolygonItem(polygon, this);
    proximityArea->setPos(-SCALE_FACTOR - (SCALE_FACTOR/5), -SCALE_FACTOR - (SCALE_FACTOR/5));

    //QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(aquireTarget()));

}
PirateShip::~PirateShip()
{
    delete timer;
    delete proximityArea;
}
void PirateShip::setSpeed(double _speed)
{
    speed = _speed;
}
double PirateShip::getSpeed()
{
    return speed;
}
double PirateShip::distanceToTarget(QGraphicsItem *target)
{
        QLineF ln(pos(), target->pos());
        return ln.length();
}
void PirateShip::rotateToPoint(QPointF p)
{
    QLineF ln(pos(), p);
    setRotation(-1 * ln.angle());
}
bool PirateShip::checkBoundries()
{
    isInBoundries = false;

    if(pos().x() > scene()->width()){
        setRotation((qrand()%80) + 140);
    }else if(pos().x() < 0){
        setRotation((qrand()%80) - 80);
    }else if(pos().y() > scene()->height()){
        setRotation((qrand()% 80) + 230 );
    }else if(pos().y() < 0){
        setRotation((qrand()% 80) + 50 );
    }else{
        isInBoundries = true;
    }

    return isInBoundries;
}
void PirateShip::aquireTarget()
{
    QList<QGraphicsItem *> targetList = proximityArea->collidingItems();
    if(targetList.size() == 1){
        hasTarget = false;
    }else{
        for(int i = 0, n = targetList.size(); i < n; ++i){
            Ship *target = dynamic_cast<Ship *>(targetList[i]);
            if(target && !target->hasBeenAttacked()){
                rotateToPoint(target->pos());
                if(!hasTarget){
                    qDebug() << "Statek piracki: Zauważyliśmy " << target->getName()
                             << "na pozycji" << target->pos() << ". Do ataku!";
                    hasTarget = true;
                }
            }
            target = nullptr;
        }
    }
    targetList.clear();
}
void PirateShip::move()
{
    //ustalanie ruchu
    theta = rotation(); //w stopniach
    dx = speed * qCos(qDegreesToRadians(theta));
    dy = speed * qSin(qDegreesToRadians(theta));
    setPos(x() + dx, y() + dy);

    //ustalanie kolizji
    QList<QGraphicsItem *> collidingShip = collidingItems();

        for(int i = 0, n = collidingShip.size(); i < n; ++i){
            Ship *ship = dynamic_cast<Ship *>(collidingShip[i]);
            if(ship && !(ship->hasBeenAttacked())){
                if(qrand()%(attack - ship->getDefense()) > attack/2){
                    scene()->removeItem(collidingShip[i]);
                    qDebug() << "Zaatakowany " << ship->getName() << " zostal zniszczony "
                             << " na pozycji " << ship->pos();
                    delete collidingShip[i];
                    emit targetDestroyed();
                }else{
                    ship->setAttacked();
                    setRotation(rotation()  + 40);
                    emit targetEngaged();
                    qDebug() << "Zaatakowany " << ship->getName() << " uniknal zniszczenia"
                             << " na pozycji " << ship->pos();
                }
        }
            ship = nullptr;
    }
    collidingItems().clear();
    checkBoundries();
}
