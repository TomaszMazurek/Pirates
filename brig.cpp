#include "brig.h"
#include "ship.h"
#include "pirateship.h"
#include "game.h"
#include <QDebug>
#include <QVector>
#include <QPolygonF>
#include <QtMath>
#include <QList>
#include <QTimer>

Brig::Brig(QString _name, double _speed, int _defense, int _scaleFactor, QObject *parent):
    Ship(_name, _speed, _defense, _scaleFactor, parent)
{
    qDebug() << "Utworzono Bryg";
}

Brig::~Brig()
{
    qDebug() << "Zniszczono Bryg";
}

