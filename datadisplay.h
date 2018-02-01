#ifndef DATADISPLAY_H
#define DATADISPLAY_H
#include <QGraphicsTextItem>
#include <QObject>

class DataDisplay: public QGraphicsTextItem
{
    Q_OBJECT

public:
    DataDisplay(QGraphicsItem *parent=0);
    ~DataDisplay();
    int getSuccess(){return success;}
    int getFailure(){return failure;}

private:
    int success;
    int failure;
public slots:
    void increaseScore();
    void increaseFailure();
};

#endif // DATADISPLAY_H
