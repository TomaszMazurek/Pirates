#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "ship.h"
#include "shipfactory.h"
#include "pirateship.h"
#include "gamedialog.h"
#include "datadisplay.h"

class Game : public QGraphicsView
{
    Q_OBJECT
public:
    Game(QWidget * parent=0);
    ~Game();
    QGraphicsScene *scene;
    GameDialog * dialog;
    ShipFactory *shipFactory;
    PirateShip *pirateShip;
    DataDisplay *score;
};

#endif // GAME_H
