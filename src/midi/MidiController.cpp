#include "MidiController.h"
#include "AkaiAPC40MkII.h"

#include <QMidiIn.h>

#include <QMap>
#include <QString>
#include <QDebug>
#include <QVariant>

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
        if(availableInputControllers.values().at(i) == "APC40 mkII")
            midiControllerList.push_back(
                new AkaiAPC40MkII(availableInputControllers.keys().at(i), 
                    availableInputControllers.values().at(i), 
                    controllerType)
                );
        else
            midiControllerList.push_back(
                new MidiController(availableInputControllers.keys().at(i), 
                    availableInputControllers.values().at(i), 
                    controllerType)
                );
    }
    return midiControllerList;
}

MidiController::MidiController(QString _key, QString _name, int _type)
    : QObject()
    , key(_key)
    , name(_name)
    , type(_type)
    , midiIn(nullptr)
    , midiOut(nullptr)
{
    if(type & InputController)
    {
        midiIn = new QMidiIn();
        if(!midiIn->connect(key))
        {
            qDebug() << "Could not connect to midi in" << key;
        }
        midiIn->start();
        connect(midiIn, SIGNAL(midiEvent(quint32, quint32)), this, SLOT(inputEventReceived(quint32, quint32)));
    }
    if(type & OutputController)
    {
        midiOut = new QMidiOut();
        midiOut->connect(key);
    }
}

MidiController::~MidiController()
{
    if(midiIn != nullptr)
    {
        midiIn->stop();
        midiIn->disconnect();
        delete midiIn;
    }
    if(midiOut != nullptr)
    {
        midiOut->disconnect();
        delete midiOut;
    }
    for(int i=0; i<controls.size(); ++i) delete controls.at(i);
}

void MidiController::inputEventReceived(quint32 message, quint32 timing)
{
    QMidiEvent event;
    event.setMessage(message);
    for(int i=0; i<controls.size(); ++i)
    {
        if(controls.at(i)->isResponsible(event))
            controls.at(i)->changeState(event);
    }

    // qDebug() << name << ":" << message << timing;
    qDebug() << name << ":" 
        << event.track()
        << event.voice()
        << event.note() 
        << event.velocity() 
        << event.amount()
        << event.number()
        << event.value()
        << event.numerator()
        << event.denominator();
}