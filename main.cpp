#include "mainwindow.h"

#include <QApplication>
#include <QSurfaceFormat>
#include <QDebug>

#include "MidiController.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QList<MidiController *> availableControllers = MidiController::availableControllers();
    for(int i=0; i<availableControllers.size(); ++i)
        qDebug() << availableControllers.at(i)->key 
            << availableControllers.at(i)->name
            << (availableControllers.at(i)->type & MidiController::InputController ? "Input":"")
            << (availableControllers.at(i)->type & MidiController::OutputController ? "Output":"");

    QSurfaceFormat format;
    format.setVersion(4,6);
    format.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(format);

    w.show();
    return a.exec();
}
