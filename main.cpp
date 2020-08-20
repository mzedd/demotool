#include "mainwindow.h"

#include <QApplication>
#include <QSurfaceFormat>
#include <QDebug>

#include "demo.h"
#include "scene/SceneObject.h"
#include "modelling/Plane.h"

//#include "MidiController.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    /*QList<MidiController *> availableControllers = MidiController::availableControllers();
    for(int i=0; i<availableControllers.size(); ++i)
        qDebug() << availableControllers.at(i)->inputKey
            << availableControllers.at(i)->outputKey 
            << availableControllers.at(i)->name
            << (availableControllers.at(i)->type & MidiController::InputController ? "Input":"")
            << (availableControllers.at(i)->type & MidiController::OutputController ? "Output":"");*/

    QSurfaceFormat format;
    format.setVersion(3,3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(format);

    w.show();
    int result = a.exec();

    /*for(int i=0; i<availableControllers.size(); ++i)
        delete availableControllers.at(i);*/

    return result;
}
