#include "shipfactory.h"
#include "cargoship.h"
#include "pirateship.h"
#include "brig.h"
#include "barque.h"
#include "game.h"
#include "datadisplay.h"
#include <random>
#include <QTime>
#include <QDebug>


ShipFactory::ShipFactory(QGraphicsScene * _scene, QObject *parent) : QObject(parent),
    scene(_scene), shipType(0)
{

}

ShipFactory::~ShipFactory()
{

}
Course ShipFactory::getPosition()
{
    QTime now = QTime::currentTime();
    qsrand((now.msec()* now.msec()));

    Course course;
    int choice = qrand()%4;
    double _x = 20, _y = 20;
    int sceneWidth = scene->width();
    int sceneHeight = scene->height();

    switch(choice){
    case 0:
        _x = qrand()% sceneWidth;
        course.angle = (qrand()% 20) + 90;

        break;

    case 1:
        _x = qrand()% sceneWidth;
        _y = sceneHeight;
        course.angle = (qrand()% 20) + 270;

        break;

    case 2:
        _y = qrand()% sceneHeight;
        course.angle = (qrand()% 10) - 10;

        break;

    case 3:
        _x = sceneWidth;
        _y = qrand()% sceneHeight;
        course.angle = (qrand()% 40) + 180;
        break;
    default:
        course.position.setX(_x);
        course.position.setY(_y);
    }

        course.position.setX(_x);
        course.position.setY(_y);

    qDebug() << "Pozycja i kąt startowy: " << course.position << " , " << course.angle;
    return course;
}
void ShipFactory::setMaxSpeed(double _speed)
{
    if(_speed > maxSpeed){
        maxSpeed = _speed;
        pirateShip->setSpeed(maxSpeed * 1.25);
    }
}
void ShipFactory::spawnShipTimer(int _shipType, int spawnTime)
{
    qDebug() << "Typ: "<< shipType;
    switch(_shipType){
    case 0: QTimer::singleShot((spawnTime * 1000), this, SLOT(spawnCargoShip()));
        break;

    case 1: QTimer::singleShot((spawnTime * 1000), this, SLOT(spawnBrig()));
        break;

    case 2: QTimer::singleShot((spawnTime * 1000), this, SLOT(spawnBarque()));
        break;

    default:
        break;
    }
}

PirateShip *ShipFactory::spawnPirateShip()
{
    pirateShip = new PirateShip();
    pirateShip->setPixmap(QPixmap(":/gfx/pirateShip.png"));
    pirateShip->setScale(0.25);
    Course course = getPosition();
    pirateShip->setPos(course.position);
    pirateShip->setRotation(course.angle);
    return pirateShip;
}

void ShipFactory::spawnCargoShip()
{
    cargoShip = new CargoShip("Frachtowiec", 2.5, 10);
    cargoShip->setPixmap(QPixmap(":/gfx/cargoShip.png"));
    cargoShip->setScale(0.4);
    Course course = getPosition();
    cargoShip->setPos(course.position);
    cargoShip->setRotation(course.angle);
    scene->addItem(cargoShip);
    setMaxSpeed(cargoShip->getSpeed());
}
void ShipFactory::spawnBrig()
{
    brig = new Brig("Bryg", 3.5, 20);
    brig->setPixmap(QPixmap(":/gfx/brig.png"));
    brig->setScale(0.35);
    Course course = getPosition();
    brig->setPos(course.position);
    brig->setRotation(course.angle);
    scene->addItem(brig);
    setMaxSpeed(brig->getSpeed());
}
void ShipFactory::spawnBarque()
{
    barque = new Barque("Bark", 4, 30);
    barque->setPixmap(QPixmap(":/gfx/barque.png"));
    barque->setScale(0.35);
    Course course = getPosition();
    barque->setPos(course.position);
    barque->setRotation(course.angle);
    scene->addItem(barque);
    setMaxSpeed(barque->getSpeed());
}
