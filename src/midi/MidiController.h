#pragma once

#include <QList>
#include <QString>
#include <QObject>

#include "ValueControl.h"

class MidiController : public QObject
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
    //! \param inputKey midi input identifier used by the controller
    //! \param outputKey midi output identifier used by the controller
    //! \param name human readable name of the controller
    //! \param type specifies input, output or both; expects ControllerType
    MidiController(QString inputKey, QString outputKey, QString name, int type);
    
    //! Destructor
    virtual ~MidiController();

    //! Gives a list of available input controllers. Also tests for output capabilities; 
    //! Controller type is set accordingly, if output capabilities are present.
    static QList<MidiController *> availableControllers();

    QString inputKey,
        outputKey,
        name;
    int type;
    QList<ValueControl *> controls;

    QMidiIn *midiIn;
    QMidiOut *midiOut;

    ValueControl *controlByName(QString name);

    signals:
    void valueControlUpdated(ValueControl *control);

    private slots:
    //! Slot for handling midi events.
    //! Sends the midi data from an event to the respective ValueControls.
    //! \param message midi message data
    //! \param timing timing value, gets redirected into "age"
    void inputEventReceived(quint32 message, quint32 timing);
};
