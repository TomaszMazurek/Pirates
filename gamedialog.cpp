#include "gamedialog.h"
#include "game.h"

GameDialog::GameDialog(QWidget *parent): QDialog(parent)
{

    createFormGroupBox();

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));


    connect(btnAdd, SIGNAL(clicked(bool)), this, SLOT(addShipListRow()));

    mainLayout = new QVBoxLayout;

    mainLayout->addWidget(formGroupBox);
    mainLayout->addWidget(buttonBox);

    setLayout(mainLayout);

    setWindowTitle(tr("Przyjmowanie danych wejsciowych symulacji"));
}
QPointF GameDialog::getSizeFromDialog()
{
    QPointF size;
    size.setX(areaWidth->text().toDouble());
    size.setY(areaHeight->text().toDouble());

    return size;

}
int GameDialog::getSimTime()
{
    return simTime->text().toInt();
}
QList<ShipData> GameDialog::getShipData()
{
    return shipDataList;
}
GameDialog::~GameDialog()
{
    delete simTime;
    delete areaWidth;
    delete areaHeight;
    delete shipSelect;
    delete shipList;
    delete spawnTime;
    delete spawnTimeList;
    delete btnAdd;

    delete right;
    delete left;
    delete center;
    delete select;
    delete dim;
    delete layout;
    delete buttonBox;
    delete formGroupBox;
    delete mainLayout;

}
void GameDialog::createFormGroupBox()
{
    formGroupBox = new QGroupBox(tr("Dane Wejsciowe"));

    layout = new QFormLayout;
    dim = new QHBoxLayout;
    select = new QVBoxLayout;
    center = new QHBoxLayout;
    left = new QVBoxLayout;
    right = new QVBoxLayout;
    
    simTime = new QLineEdit();
    simTime->setValidator(new QIntValidator(0, 1000, this)); //walidacja typu int i ograniczenie 1000 sekund

    areaWidth = new QLineEdit();
    areaWidth->setToolTip("Szerokość");
    areaWidth->setText("1600");
    areaWidth->setValidator(new QIntValidator(0, 1920, this));//walidacja typu i ograniczenie do max szerokości

    areaHeight = new QLineEdit();
    areaHeight->setToolTip("Wysokość");
    areaHeight->setText("1000");
    areaHeight->setValidator(new QIntValidator(0,1080, this));//walidacja typu i ograniczenie do max wysokości

    shipSelect = new QComboBox();
    shipSelect->addItem("Frachtowiec : prędkość 3", 0);
    shipSelect->addItem("Bryg : prędkość 4", 1);
    shipSelect->addItem("Bark : prędkość 5", 2);

    shipList = new QListWidget();
    shipList->setToolTip("Lista statków dla symulacji");

    spawnTime = new QLineEdit();
    spawnTime->setValidator(new QIntValidator(0, 999,this));//walidacja typu i ograniczenie do czasu trwania symulacji
    spawnTimeList = new QListWidget();
    spawnTimeList->setToolTip("Lista czasów dla poszczególnych statków podczas trwania symulacji");

    btnAdd = new QPushButton("Dodaj do list");
    btnAdd->setToolTip("Dodaje do list wartości zadane powyżej nich. Obowiązkowo należy wypełnić oba pola: "
                       "listę staków oraz czas pojawienia się na planszy");
    
    left->addWidget(shipSelect);
    left->addWidget(shipList);

    right->addWidget(spawnTime);
    right->addWidget(spawnTimeList);

    center->addLayout(left);
    center->addLayout(right);
    
    select->addLayout(center);
    select->addWidget(btnAdd);

    dim->addWidget(areaWidth);
    dim->addWidget(areaHeight);

    layout->addRow(new QLabel(tr("Czas trwania symulacji (w sekundach)")), simTime);
    layout->addRow(new QLabel(tr("Rozmiar patrolowanego obszaru")), dim);
    layout->addRow(new QLabel(tr("Lista statków i czasów pojawienia się")), select);

    formGroupBox->setLayout(layout);
}
void GameDialog::addShipListRow()
{

    if(spawnTime->text().length() != 0){

        ShipData data;
        data.type = shipSelect->currentData().toInt();
        data.spawnTime = spawnTime->text().toInt();

        shipList->addItem(shipSelect->currentText());
        spawnTimeList->addItem("Czas Pojawienia się: +" + spawnTime->text() + " sek");
        shipDataList.append(data);
    }
}
