#pragma once

#include <QString>
#include <QColor>

#include <QMidiIn.h>
#include <QMidiOut.h>
#include <QMidiFile.h>

//! ValueControl state class. Knows how to process incoming midi messages by a `messageFormat` that you provide specifically
//  for each MIDI controller you want to use.
class ValueControl
{
    public:
    //! Enum for specifying which bytes should be checked when parsing midi messages. Note that they must be ordered.
    typedef enum
    {
        Track = 1,
        Voice = 2,
        Note = 4, 
        Velocity = 8,
        Amount = 16,
        Number = 32,
        Value = 64,
        Numerator = 128,
        Denominator = 256
    } MessageFormat;

    //! Constructor
    /*! 
     * Example:
     * \code{.cpp}
     * ValueControl *fader = new ValueControl(Track | Amount)
     * \endcode
     * \param name human readable name for the specific control
     * \param inputIdFormat use MessageFormat to construct the format from the bytes that should be matched when checking responsibility.
     * \param inputValueFormat use MessageFormat to construct the format from the bytes that shoudl be extracted when processing incoming midi messages.
     * \param inputId input Id to check for, in the same order as inputIdFormat.
     * \param outputIdFormat use MessageFormat to construct the format used for creating output messages.
     * \param outputValueFormat use MessageFormat to pass the information which fields should be used to transport output values.
     * \param outputId output Id to check for, in the same order as outputIdFormat.
     */ 
    ValueControl(QString name, int inputIdFormat, int inputValueFormat, QList<int> inputId, int outputIdFormat, int outputValueFormat, QList<int> outputId);

    //! Destructor
    virtual ~ValueControl();

    //! Floating point value of the ValueControl state in the closed interval between 0 and 1.
    float floatValue();

    //! Integer value of the ValueControl state in the closed interval between 0 and 127.
    int intValue();

    //! Bool value of the state; useful for midi keyboard keys or buttons
    bool boolValue();

    //! Change the state of the ValueControl with the specific midi event contained in message.
    //! \param message message to parse with messageFormat instructions
    void changeState(QMidiEvent message);

    //! Check if this specific ValueControl is responsible for message with the available messageFormat.
    //! \param message MIDI message to check responsibility for.
    bool isResponsible(QMidiEvent message);

    //! Find the nearest color index to the QColor specified and create a midi message lighting this color.
    QMidiEvent lightColor(QColor color);

    //! Check if out put message format allows setting of values (as the case with motor faders)
    bool canSetValues();

    //! set Value to the value nearest to the supplied floating point value and construct MIDI message.
    QMidiEvent setValue(float value);

    //! set Value to the specific integer value supplied here and return QMidiEvent representing that
    QMidiEvent setValue(int value);

    private:
    int value,
        inputIdFormat,
        inputValueFormat,
        outputIdFormat,
        outputValueFormat;
    QList<int> inputId,
        outputId;
    bool on;
    QString name;
};
