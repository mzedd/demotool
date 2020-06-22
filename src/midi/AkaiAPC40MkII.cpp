#include "AkaiAPC40MkII.h"
#include "ValueControl.h"

AkaiAPC40MkII::AkaiAPC40MkII(QString _key, QString _name, int _type)
    : MidiController(_key, _name, _type)
{
    // Lower faders
    QList<int> idList;
    idList << -1 << 0 << -1 << -1 << -1 << 7 << -1 << -1;
    controls.push_back(new ValueControl("Fader 0", ValueControl::Track | ValueControl::Voice | ValueControl::Note | ValueControl::Velocity | ValueControl::Amount | ValueControl::Number | ValueControl::Numerator | ValueControl::Denominator, ValueControl::Value, idList, 0, 0, QList<int>()));
    idList[1] = 1;
    controls.push_back(new ValueControl("Fader 1", ValueControl::Track | ValueControl::Voice | ValueControl::Note | ValueControl::Velocity | ValueControl::Amount | ValueControl::Number | ValueControl::Numerator | ValueControl::Denominator, ValueControl::Value, idList, 0, 0, QList<int>()));
    idList[1] = 2;
    controls.push_back(new ValueControl("Fader 2", ValueControl::Track | ValueControl::Voice | ValueControl::Note | ValueControl::Velocity | ValueControl::Amount | ValueControl::Number | ValueControl::Numerator | ValueControl::Denominator, ValueControl::Value, idList, 0, 0, QList<int>()));
    idList[1] = 3;
    controls.push_back(new ValueControl("Fader 3", ValueControl::Track | ValueControl::Voice | ValueControl::Note | ValueControl::Velocity | ValueControl::Amount | ValueControl::Number | ValueControl::Numerator | ValueControl::Denominator, ValueControl::Value, idList, 0, 0, QList<int>()));
    idList[1] = 4;
    controls.push_back(new ValueControl("Fader 4", ValueControl::Track | ValueControl::Voice | ValueControl::Note | ValueControl::Velocity | ValueControl::Amount | ValueControl::Number | ValueControl::Numerator | ValueControl::Denominator, ValueControl::Value, idList, 0, 0, QList<int>()));
    idList[1] = 5;
    controls.push_back(new ValueControl("Fader 5", ValueControl::Track | ValueControl::Voice | ValueControl::Note | ValueControl::Velocity | ValueControl::Amount | ValueControl::Number | ValueControl::Numerator | ValueControl::Denominator, ValueControl::Value, idList, 0, 0, QList<int>()));
    idList[1] = 6;
    controls.push_back(new ValueControl("Fader 6", ValueControl::Track | ValueControl::Voice | ValueControl::Note | ValueControl::Velocity | ValueControl::Amount | ValueControl::Number | ValueControl::Numerator | ValueControl::Denominator, ValueControl::Value, idList, 0, 0, QList<int>()));
    idList[1] = 7;
    controls.push_back(new ValueControl("Fader 7", ValueControl::Track | ValueControl::Voice | ValueControl::Note | ValueControl::Velocity | ValueControl::Amount | ValueControl::Number | ValueControl::Numerator | ValueControl::Denominator, ValueControl::Value, idList, 0, 0, QList<int>()));
    
    // Main fader
    idList[1] = 0;
    idList[5] = 14;
    controls.push_back(new ValueControl("Main fader", ValueControl::Track | ValueControl::Voice | ValueControl::Note | ValueControl::Velocity | ValueControl::Amount | ValueControl::Number | ValueControl::Numerator | ValueControl::Denominator, ValueControl::Value, idList, 0, 0, QList<int>()));
    
}

AkaiAPC40MkII::~AkaiAPC40MkII()
{
}