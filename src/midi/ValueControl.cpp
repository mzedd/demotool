#include "ValueControl.h"

ValueControl::ValueControl(QString _inputMessageFormat, QString _outputMessageFormat)
    : inputMessageFormat(_inputMessageFormat)
    , outputMessageFormat(_outputMessageFormat)
    , age(0)
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

int ValueControl::currentAge()
{
    return age;
}

bool ValueControl::isResponsible(QMidiEvent message)
{
    return true;
}

void ValueControl::changeState(QMidiEvent message)
{

}