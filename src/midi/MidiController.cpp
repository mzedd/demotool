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
        if(availableOutputControllers.values().contains(availableInputControllers.values().at(i)))
            controllerType = InputController | OutputController;
        QString inputControllerName = availableInputControllers.values().at(i);
        if(inputControllerName == "KeyStep Pro MIDI IN")
            inputControllerName = "KeyStep Pro MIDI OUT";
        QString outputKey = availableOutputControllers.keys().at(availableOutputControllers.values().indexOf(inputControllerName));
        if(availableInputControllers.values().at(i) == "APC40 mkII")
        {
            midiControllerList.push_back(
                new AkaiAPC40MkII(availableInputControllers.keys().at(i), 
                    outputKey, 
                    availableInputControllers.values().at(i), 
                    controllerType)
                );
        }
        else
            midiControllerList.push_back(
                new MidiController(availableInputControllers.keys().at(i), 
                    outputKey,
                    availableInputControllers.values().at(i), 
                    controllerType)
                );
    }
    return midiControllerList;
}

MidiController::MidiController(QString _inputKey, QString _outputKey, QString _name, int _type)
    : QObject()
    , inputKey(_inputKey)
    , outputKey(_outputKey)
    , name(_name)
    , type(_type)
    , midiIn(nullptr)
    , midiOut(nullptr)
{
    if(type & InputController)
    {
        midiIn = new QMidiIn();
        if(!midiIn->connect(inputKey))
        {
            qDebug() << "Could not connect to midi in" << inputKey;
        }
        midiIn->start();
        connect(midiIn, SIGNAL(midiEvent(quint32, quint32)), this, SLOT(inputEventReceived(quint32, quint32)));
    }
    if(type & OutputController)
    {
        midiOut = new QMidiOut();
        if(!midiOut->connect(outputKey))
        {
            qDebug() << "Could not connect to midi out" << outputKey;
        }
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
        {
            controls.at(i)->changeState(event);
            emit valueControlUpdated(controls.at(i));
        }
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
        << event.denominator()
        << event.type();
}

ValueControl *MidiController::controlByName(QString name)
{
    for(int i=0; i<controls.size(); ++i)
        if(controls.at(i)->name == name) return controls.at(i);
    return nullptr;
}
