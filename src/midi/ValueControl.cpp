#include "ValueControl.h"

#include <QDebug>

ValueControl::ValueControl(QString _name, int _inputIdFormat, int _inputValueFormat, QList<int> _inputId, int _outputIdFormat, int _outputValueFormat, QList<int> _outputId)
    : name(_name)
    , inputIdFormat(_inputIdFormat)
    , inputValueFormat(_inputValueFormat)
    , inputId(_inputId)
    , outputIdFormat(_outputIdFormat)
    , outputValueFormat(_outputValueFormat)
    , outputId(_outputId)
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
    return responsibility;
}

void ValueControl::changeState(QMidiEvent message)
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
    qDebug() << name << ": new value " << value;
}

QMidiEvent ValueControl::lightColor(QColor color)
{
    QList<QColor> availableColors;
    return QMidiEvent();
}