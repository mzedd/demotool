#include "MidiController.h"

#include <QMidiIn.h>

#include <QMap>
#include <QString>
#include <QDebug>

QList<MidiController *> MidiController::availableControllers()
{
    QMap<QString, QString> availableInputControllers = QMidiIn::devices(),
        availableOutputControllers = QMidiOut::devices();
    QList<MidiController *> midiControllerList;
    for(int i=0; i<availableInputControllers.size(); ++i)
    {
        int controllerType = InputController;
        if(availableOutputControllers.keys().contains(availableInputControllers.keys().at(i)))
            controllerType = InputController | OutputController;
        midiControllerList.push_back(
            new MidiController(availableInputControllers.keys().at(i), 
                availableInputControllers.values().at(i), 
                controllerType)
            );
    }
    return midiControllerList;
}

MidiController::MidiController(QString _key, QString _name, int _type)
    : key(_key)
    , name(_name)
    , type(_type)
    , midiIn(nullptr)
    , midiOut(nullptr)
{
    if(type & InputController)
    {
        midiIn = new QMidiIn();
        midiIn->connect(key);
    }
    if(type & OutputController)
    {
        midiOut = new QMidiOut();
        midiOut->connect(key);
    }
}

MidiController::~MidiController()
{

}