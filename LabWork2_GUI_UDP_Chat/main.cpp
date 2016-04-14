#include "mainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow mainWin(argc);
    mainWin.show();

    return app.exec();
}
