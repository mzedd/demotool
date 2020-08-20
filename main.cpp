#include <QApplication>
#include <QSurfaceFormat>
#include <QDebug>

#include "mainwindow.h"
#include "demo.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QSurfaceFormat format;
    format.setVersion(3,3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(format);

    w.show();
    int result = a.exec();

    return result;
}
