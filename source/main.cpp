#include <QApplication>
#include <QDebug>

#include "mainwindow.h"
#include "app/app_icons.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    MainWindow w;
    w.setWindowIcon(*AppIcons::MAIN);
    w.show();
    return a.exec();
}
