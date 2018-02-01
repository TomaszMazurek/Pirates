#ifndef GAMEDIALOG_H
#define GAMEDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>
#include <QComboBox>
#include <QDialogButtonBox>
#include <QCheckBox>
#include <QListWidget>
#include <QPointF>
#include <QFormLayout>


struct ShipData{
    int type;
    int spawnTime;
};

class GameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GameDialog(QWidget *parent = 0);
    QPointF getSizeFromDialog();
    int getSimTime();
    QList<ShipData> getShipData();
    QDialogButtonBox *buttonBox;
    ~GameDialog();

private:
    QList<ShipData> shipDataList;
    void createFormGroupBox();

    QGroupBox *formGroupBox;
    QLineEdit *simTime;
    QLineEdit *areaHeight;
    QLineEdit *areaWidth;
    QComboBox *shipSelect;
    QListWidget *shipList;
    QLineEdit *spawnTime;
    QListWidget *spawnTimeList;
    QPushButton *btnAdd;

    QFormLayout *layout;
    QHBoxLayout *dim;
    QVBoxLayout *select;
    QHBoxLayout *center;
    QVBoxLayout *left;
    QVBoxLayout *right;
    QVBoxLayout *mainLayout;

public slots:
    void addShipListRow();

};

#endif // GAMEDIALOG_H
