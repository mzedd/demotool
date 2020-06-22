#pragma once

#include <QList>
#include <QString>

#include "ValueControl.h"

class MidiController
{
    public:
    typedef enum ControllerType
    {
        InputController = 1,
        OutputController = 2
    };
    MidiController(QString key, QString name, int type);
    virtual ~MidiController();

    int faderIntValue(int index);
    float faderFloatValue(int index);

    //! Gives a list of available input controllers. Also tests for output capabilities; 
    //! Controller type is set accordingly, if output capabilities are present.
    static QList<MidiController *> availableControllers();

    QString key,
        name;
    int type;
    
    private:
    QList<ValueControl> faders;
    QList<ValueControl> knobs;
    QList<ValueControl> horizontalSliders;
    QList<ValueControl> buttons;

    QMidiIn *midiIn;
    QMidiOut *midiOut;
};
