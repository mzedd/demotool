#pragma once

#include <QList>
#include <QString>
#include <QObject>

#include "ValueControl.h"

class MidiController : QObject
{
    Q_OBJECT

    public:
    //! Enum for identifying input or output functionality
    typedef enum ControllerType
    {
        InputController = 1,
        OutputController = 2
    };

    //! Constructs the midi controller class with
    //! \param key midi identifier used by the controller
    //! \param name human readable name of the controller
    //! \param type specifies input, output or both; expects ControllerType
    MidiController(QString key, QString name, int type);
    
    //! Destructor
    virtual ~MidiController();

    //! Gives a list of available input controllers. Also tests for output capabilities; 
    //! Controller type is set accordingly, if output capabilities are present.
    static QList<MidiController *> availableControllers();

    QString key,
        name;
    int type;
    QList<ValueControl *> controls;

    private:

    QMidiIn *midiIn;
    QMidiOut *midiOut;

    private slots:
    //! Slot for handling midi events.
    //! Sends the midi data from an event to the respective ValueControls.
    //! \param message midi message data
    //! \param timing timing value, gets redirected into "age"
    void inputEventReceived(quint32 message, quint32 timing);
};
