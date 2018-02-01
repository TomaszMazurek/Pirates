#ifndef SHIP_H
#define SHIP_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QString>


class Ship : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    explicit Ship(QString _name, double _speed, int _defense, int _scaleFactor, QObject *parent = nullptr);
    ~Ship();
    bool hasBeenAttacked(){return attacked;}
    void setAttacked(){attacked = true;}
    int getDefense(){return defense;}
    void changeCourse();
    double getSpeed(){return speed;}
    void setSpeed(double _speed){speed = _speed;}
    QString getName(){return name;}

private:
    QGraphicsPolygonItem *proximityArea;
    QTimer *timer;
    bool enemyApproaching;
    bool attacked;
    double speed;
    double theta;
    double dx;
    double dy;
    int defense;
    int SCALE_FACTOR;
    QString name;
signals:

public slots:
    virtual void move();
    void proximityAlert();

};

#endif // SHIP_H
