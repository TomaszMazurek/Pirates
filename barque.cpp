#include "barque.h"
#include "ship.h"
#include "pirateship.h"
#include "game.h"
#include <QDebug>
#include <QVector>
#include <QPolygonF>
#include <QList>
#include <QTimer>


Barque::Barque(QString _name, double _speed, int _defense, int _scaleFactor, QObject *parent):
    Ship(_name, _speed, _defense, _scaleFactor,  parent)
{
    qDebug() << "Utworzono Bark";
}

Barque::~Barque()
{

    qDebug() << "Zniszczono Bark";
}

