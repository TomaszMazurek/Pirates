#include "ship.h"
#include "pirateship.h"
#include <QList>
#include <QTimer>
#include <QDebug>
#include <QtMath>

Ship::Ship(QString _name, double _speed, int _defense, int _scaleFactor, QObject *parent) : QObject(parent),
    name(_name), speed(_speed), defense(_defense), SCALE_FACTOR(_scaleFactor)
{
    attacked = false;
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(40);

    //utworzenie wektora współrzędnych dla poligonu
    QVector<QPointF> proximityVector;
    proximityVector << QPoint(1,0) << QPoint(2,0) << QPoint(3,1) << QPoint(3,2)<< QPoint(2,3)
              << QPoint(1,3) << QPoint(0,2) << QPoint(0,1);

    //skalowanie obszaru zbliżenia
    for(int i = 0, n = proximityVector.size(); i < n; ++i){
        proximityVector[i] *= SCALE_FACTOR;
    }

    //utworzenie poligonu dla obszaru zbliżenia
    QPolygonF polygon(proximityVector);
    proximityArea = new QGraphicsPolygonItem(polygon, this);
    proximityArea->setPos(-SCALE_FACTOR - (SCALE_FACTOR/5), -SCALE_FACTOR - (SCALE_FACTOR/5));

    //QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(proximityAlert()));
}
Ship::~Ship()
{
    delete proximityArea;
    delete timer;
}
void Ship::proximityAlert()
{

    QList<QGraphicsItem *> enemyList = proximityArea->collidingItems();
    if(enemyList.size() == 1){
        enemyApproaching = false;
    }else{
        for(int i = 0, n = enemyList.size(); i < n; ++i){
            PirateShip *enemy = dynamic_cast<PirateShip *>(enemyList[i]);
            if(enemy && !enemyApproaching && !attacked){
                this->changeCourse();
                enemyApproaching = true;
                qDebug() << "MayDay! Jestesmy na pozycji " << this->pos()
                         << "\nStatek piracki namierza nasz " << this->getName() << " !. Uciekamy !";
            }
        }
    }
        enemyList.clear();
}
void Ship::changeCourse()
{
    qDebug() << this->getName() << " zmienia kurs";
    qreal width = scene()->width();
    qreal height = scene()->height();
    qreal widthRatio = width/x();
    qreal heightRatio = height/y();
    qreal widthMiddle = width/(width/2);
    qreal heightMiddle = height/(height/2);

    if(widthRatio < widthMiddle){
        if(heightRatio < heightMiddle){
            if(heightRatio > widthRatio){
                setRotation(90);
            }else{
                setRotation(0);
            }
        }else{
            if(heightRatio < widthRatio){
                setRotation(270);
            }else{
                setRotation(0);
            }
        }
    }else{
        if(heightRatio < heightMiddle){
            if(heightRatio > widthRatio){
                setRotation(90);
            }else{
                setRotation(180);
            }
        }else{
            if(heightRatio < widthRatio){
                setRotation(270);
            }else{
                setRotation(180);
            }
        }
    }
}
void Ship::move()
{
    //ustalanie ruchu
    theta = rotation(); //w stopniach
    dx = speed * qCos(qDegreesToRadians(theta));
    dy = speed * qSin(qDegreesToRadians(theta));

    setPos(x() + dx, y() + dy);

    //wyjscie poza widok
    if(pos().x() > 1700 || pos().y() > 1100 ||
            pos().x() < -100 || pos().y() < -100){
        //attacked = true;
        qDebug() << this->getName() << "wyszedl poza obszar";
        delete this;
    }
}
