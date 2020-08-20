#include "ValueControl.h"

#include <QDebug>

ValueControl::ValueControl(QString _name, int _inputIdFormat, int _inputValueFormat, QList<int> _inputId, int _outputIdFormat, int _outputValueFormat, QList<int> _outputId, bool _differential)
    : name(_name)
    , inputIdFormat(_inputIdFormat)
    , inputValueFormat(_inputValueFormat)
    , inputId(_inputId)
    , outputIdFormat(_outputIdFormat)
    , outputValueFormat(_outputValueFormat)
    , outputId(_outputId)
    , differential(_differential)
{

}

ValueControl::~ValueControl()
{

}

float ValueControl::floatValue()
{
    return (float)value/(float)0x7f;
}

int ValueControl::intValue()
{
    return value;
}

bool ValueControl::boolValue()
{
    return value == 127;
}

bool ValueControl::isResponsible(QMidiEvent message)
{
    bool responsibility = true;
    int compareIndex = 0;
    if(inputIdFormat & Track) responsibility = responsibility && (message.track() == inputId.at(compareIndex++));
    if(inputIdFormat & Voice) responsibility = responsibility && (message.voice() == inputId.at(compareIndex++));
    if(inputIdFormat & Note) responsibility = responsibility && (message.note() == inputId.at(compareIndex++));
    if(inputIdFormat & Velocity) responsibility = responsibility && (message.velocity() == inputId.at(compareIndex++));
    if(inputIdFormat & Amount) responsibility = responsibility && (message.amount() == inputId.at(compareIndex++));
    if(inputIdFormat & Number) responsibility = responsibility && (message.number() == inputId.at(compareIndex++));
    if(inputIdFormat & Value) responsibility = responsibility && (message.value() == inputId.at(compareIndex++));
    if(inputIdFormat & Numerator) responsibility = responsibility && (message.numerator() == inputId.at(compareIndex++));
    if(inputIdFormat & Denominator) responsibility = responsibility && (message.denominator() == inputId.at(compareIndex++));
    if(inputIdFormat & Type) responsibility = responsibility && (message.type() == inputId.at(compareIndex++));
    return responsibility;
}

void ValueControl::changeState(QMidiEvent message)
{
    if(differential)
    {
        if(inputValueFormat & Track) value += message.track()<65?message.track():message.track()-128;
        if(inputValueFormat & Voice) value += message.voice()<65?message.voice():message.voice()-128;
        if(inputValueFormat & Note) value += message.note()<65?message.note():message.note()-128;
        if(inputValueFormat & Velocity) value += message.velocity()<65?message.velocity():message.velocity()-128;
        if(inputValueFormat & Amount) value += message.amount()<65?message.amount():message.amount()-128;
        if(inputValueFormat & Number) value += message.number()<65?message.number():message.number()-128;
        if(inputValueFormat & Value) value += message.value()<65?message.value():message.value()-128;
        if(inputValueFormat & Numerator) message.numerator()<65?value += message.numerator():message.numerator()-128;
        if(inputValueFormat & Denominator) message.denominator()<65?value += message.denominator():message.denominator()-128;
        if(inputValueFormat & Type) message.type()<65?value += message.type():message.type()-128;
    }
    else
    {
        if(inputValueFormat & Track) value = message.track();
        if(inputValueFormat & Voice) value = message.voice();
        if(inputValueFormat & Note) value = message.note();
        if(inputValueFormat & Velocity) value = message.velocity();
        if(inputValueFormat & Amount) value = message.amount();
        if(inputValueFormat & Number) value = message.number();
        if(inputValueFormat & Value) value = message.value();
        if(inputValueFormat & Numerator) value = message.numerator();
        if(inputValueFormat & Denominator) value = message.denominator();
        if(inputValueFormat & Type) value = message.type();
    }

    emit valueChanged(this, value);
    emit updateOutputs(this, outputValue);
}

QMidiEvent ValueControl::setValue(int value)
{
    QMidiEvent event;
    int compareIndex = 0;
    event.setType(QMidiEvent::NoteOn);
    if(outputIdFormat & Track) event.setTrack(outputId.at(compareIndex++));
    if(outputIdFormat & Voice) event.setVoice(outputId.at(compareIndex++));
    if(outputIdFormat & Note) event.setNote(outputId.at(compareIndex++));
    if(outputIdFormat & Velocity) event.setVelocity(outputId.at(compareIndex++));
    if(outputIdFormat & Amount) event.setAmount(outputId.at(compareIndex++));
    if(outputIdFormat & Number) event.setNumber(outputId.at(compareIndex++));
    if(outputIdFormat & Value) event.setValue(outputId.at(compareIndex++));
    if(outputIdFormat & Numerator) event.setNumerator(outputId.at(compareIndex++));
    if(outputIdFormat & Denominator) event.setDenominator(outputId.at(compareIndex++));
    if(outputIdFormat & Type) event.setType((QMidiEvent::EventType)outputId.at(compareIndex++));
    if(inputValueFormat & Track) event.setTrack(value);
    if(inputValueFormat & Voice) event.setVoice(value);
    if(inputValueFormat & Note) event.setNote(value);
    if(inputValueFormat & Velocity) event.setVelocity(value);
    if(inputValueFormat & Amount) event.setAmount(value);
    if(inputValueFormat & Number) event.setNumber(value);
    if(inputValueFormat & Value) event.setValue(value);
    if(inputValueFormat & Numerator) event.setNumerator(value);
    if(inputValueFormat & Denominator) event.setDenominator(value);
    if(inputValueFormat & Type) event.setType((QMidiEvent::EventType)value);
    outputValue = value;
    emit outputValueChanged(value);
    return event;
}
