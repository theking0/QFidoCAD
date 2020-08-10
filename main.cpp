#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationName("FMSoft");
    a.setOrganizationDomain("FMGroup");
    a.setApplicationName("QFidoCAD");
    MainWindow w;
    w.show();
    return a.exec();
}
