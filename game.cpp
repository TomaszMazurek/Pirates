#include "game.h"
#include "gamedialog.h"
#include "QTimer"
#include <QDebug>


Game::Game(QWidget * parent): QGraphicsView(parent)
{
    dialog = new GameDialog(parent);
    dialog->exec();

    QList<ShipData> shipData = dialog->getShipData();

    QTimer::singleShot((dialog->getSimTime() * 1000), this, SLOT(close()));

    int xSize = dialog->getSizeFromDialog().x();
    int ySize = dialog->getSizeFromDialog().y();


    //scena
    scene = new QGraphicsScene(this);
    scene->setBackgroundBrush(QBrush(QImage(":/gfx/sea2.jpg").scaled(xSize,ySize, Qt::KeepAspectRatioByExpanding)));
    scene->setSceneRect(0,0, xSize, ySize);


    //widok
    setScene(scene);

    setFixedSize(xSize, ySize);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //statki
    shipFactory = new ShipFactory(scene);
    pirateShip = shipFactory->spawnPirateShip();
    scene->addItem(pirateShip);

    for(int i = 0; i < shipData.size(); ++i){
        shipFactory->spawnShipTimer(shipData[i].type,shipData[i].spawnTime);
    }

    //do testów
    shipFactory->spawnBrig();
    shipFactory->spawnBarque();
    shipFactory->spawnCargoShip();

    //wyniki
    score = new DataDisplay();
    scene->addItem(score);
    connect(pirateShip, SIGNAL(targetDestroyed()), score, SLOT(increaseScore()));
    connect(pirateShip, SIGNAL(targetEngaged()), score, SLOT(increaseFailure()));

}

Game::~Game()
{

    delete score;
    delete pirateShip;
    delete shipFactory;
    delete scene;
    delete dialog;
}
