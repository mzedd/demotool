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
    //! Constructor
    /*! \param inputMessageFormat construct a string with byte meanings of incoming midi messages.
     *  <table>
     *      <th><td>id</td><td>meaning</td></th>
     *      <tr><td>@vh</td><td>value high byte</td></tr>
     *      <tr><td>@vl</td><td>value low byte</td></tr>
     *      <tr><td>@idh1</td><td>highest id byte</td></tr>
     *      <tr><td>@idh2</td><td>second highest id byte</td></tr>
     *      <tr><td>@idh3</td><td>third highest id byte</td></tr>
     *      <tr><td>@ida1</td><td>highest age byte</td></tr>
     *  </table>
     *  \param outputMessageFormat construct a string with byte meanings of outgoing midi messages.
     */ 
    ValueControl(QString inputMessageFormat, QString outputMessageFormat = "");

    //! Destructor
    virtual ~ValueControl();

    //! Floating point value of the ValueControl state in the closed interval between 0 and 1.
    float floatValue();

    //! Integer value of the ValueControl state in the closed interval between 0 and 127.
    int intValue();

    //! Bool value of the state; useful for midi keyboard keys or buttons
    bool boolValue();

    //! Integer value for the "age" of the ValueControl (how much ValueControl ticks have already happened).
    int currentAge();

    //! Change the state of the ValueControl with the specific midi event contained in message.
    //! \param message message to parse with messageFormat instructions
    void changeState(QMidiEvent message);

    //! Check if this specific ValueControl is responsible for message with the available messageFormat.
    //! \param message MIDI message to check responsibility for.
    bool isResponsible(QMidiEvent message);

    //! Check if output message format for colored buttons can be constructed
    bool canLightColor();

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
        age;
    bool on;
    QString inputMessageFormat,
        outputMessageFormat;
};
