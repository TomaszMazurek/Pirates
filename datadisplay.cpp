#include "datadisplay.h"
#include <QFont>
#include <QDebug>

DataDisplay::DataDisplay(QGraphicsItem *parent): QGraphicsTextItem(parent),
    success(0), failure(0)
{
    setPlainText("Sukcesów: " + QString::number(success) + "    Porażek " + QString::number(failure));
    setDefaultTextColor(Qt::red);
    setFont(QFont("times", 16));
}
DataDisplay::~DataDisplay()
{
    qDebug() << "Osiągniętych sukcesów : "<< success
             << "\nPoniesionych porażek : " << failure ;
}
void DataDisplay::increaseScore()
{
    ++success;
    setPlainText("Sukcesów: " + QString::number(success) + "    Porażek " + QString::number(failure));

}
void DataDisplay::increaseFailure()
{
    ++failure;
    setPlainText("Sukcesów: " + QString::number(success) + "    Porażek " + QString::number(failure));
}
