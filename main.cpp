#include <QApplication>
#include <QPushButton>
#include "game.h"
#include "gamedialog.h"
//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Game game;
    game.show();

    //_CrtDumpMemoryLeaks();
    return a.exec();
}
