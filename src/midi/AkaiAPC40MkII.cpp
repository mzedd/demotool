#include "AkaiAPC40MkII.h"
#include "ValueControl.h"

#include <cmath>

#include <QDebug>

AkaiAPC40MkII::AkaiAPC40MkII(QString _inputKey, QString _outputKey, QString _name, int _type)
    : MidiController(_inputKey, _outputKey, _name, _type)
{
    // Lower faders
    QList<int> idList;
    idList << -1 << 0 << -1 << -1 << -1 << 7 << -1 << -1;
    for(int i=0; i<8; ++i)
    {
        idList[1] = i;
        controls.push_back(new ValueControl("Fader " + QString::number(i), ValueControl::Track | ValueControl::Voice | ValueControl::Note | ValueControl::Velocity | ValueControl::Amount | ValueControl::Number | ValueControl::Numerator | ValueControl::Denominator, ValueControl::Value, idList, 0, 0, QList<int>()));
    }
    
    // Main fader
    idList[1] = 0;
    idList[5] = 14;
    controls.push_back(new ValueControl("Main fader", ValueControl::Track | ValueControl::Voice | ValueControl::Note | ValueControl::Velocity | ValueControl::Amount | ValueControl::Number | ValueControl::Numerator | ValueControl::Denominator, ValueControl::Value, idList, 0, 0, QList<int>()));
    
    // Horizontal slider
    idList[5] = 15;
    controls.push_back(new ValueControl("Horizontal slider", ValueControl::Track | ValueControl::Voice | ValueControl::Note | ValueControl::Velocity | ValueControl::Amount | ValueControl::Number | ValueControl::Numerator | ValueControl::Denominator, ValueControl::Value, idList, 0, 0, QList<int>()));
    
    // Right per-bank knobs
    idList.clear();
    idList << -1 << 0 << -1 << -1 << -1 << 16 << -1 << -1;
    for(int i=0; i<8; ++i) // Bank index
    {
        for(int j=0; j<8; ++j) // Knob index
        {
            idList[1] = i;
            idList[5] = 16+j;
            controls.push_back(new ValueControl("Bank " + QString::number(i) + " knob " + QString::number(j), ValueControl::Track | ValueControl::Voice | ValueControl::Note | ValueControl::Velocity | ValueControl::Amount | ValueControl::Number | ValueControl::Numerator | ValueControl::Denominator, ValueControl::Value, idList, 0, 0, QList<int>()));
        }
    }
    // Master bank right knobs
    for(int j=0; j<8; ++j) // Knob index
    {
        idList[1] = 8;
        idList[5] = 16+j;
        controls.push_back(new ValueControl("Master Bank knob " + QString::number(j), ValueControl::Track | ValueControl::Voice | ValueControl::Note | ValueControl::Velocity | ValueControl::Amount | ValueControl::Number | ValueControl::Numerator | ValueControl::Denominator, ValueControl::Value, idList, 0, 0, QList<int>()));
    }

    // Top knobs
    idList.clear();
    idList << -1 << 0 << -1 << -1 << -1 << 48 << -1 << -1;
    for(int i=0; i<8; ++i)
    {
        idList[5] = 48 + i;
        controls.push_back(new ValueControl("Top knob " + QString::number(i), ValueControl::Track | ValueControl::Voice | ValueControl::Note | ValueControl::Velocity | ValueControl::Amount | ValueControl::Number | ValueControl::Numerator | ValueControl::Denominator, ValueControl::Value, idList, 0, 0, QList<int>()));
    }

    // Button matrix
    idList.clear();
    int mask = ValueControl::Track | ValueControl::Voice | ValueControl::Note | ValueControl::Amount | ValueControl::Number | ValueControl::Value | ValueControl::Numerator | ValueControl::Denominator;
    idList << -1 << 0 << 0 << -1 << -1 << -1 << -1 << -1;
    for(int i=0; i<40; ++i)
    {
        idList[2] = i;
        controls.push_back(new ValueControl("Matrix Button " + QString::number(i), mask, ValueControl::Velocity, idList, mask, ValueControl::Velocity, idList));    }

    // Scene launch line right of button matrix
    for(int i=0; i<5; ++i)
    {
        idList[2] = 82 + i;
        controls.push_back(new ValueControl("Scene launch Button " + QString::number(i), mask, ValueControl::Velocity, idList, mask, ValueControl::Velocity, idList));
    }

    // Clip stop row below button matrix
    idList.clear();
    idList << -1 << 0 << 52 << -1 << -1 << -1 << -1 << -1;
    for(int i=0; i<8; ++i)
    {
        idList[1] = i;
        controls.push_back(new ValueControl("Clip Stop Button " + QString::number(i), ValueControl::Track | ValueControl::Voice | ValueControl::Note | ValueControl::Amount | ValueControl::Number | ValueControl::Value | ValueControl::Numerator | ValueControl::Denominator, ValueControl::Velocity, idList, 0, 0, QList<int>()));
    }

    // Tri-State 'A|B' buttons below the bank select row
    idList.clear();
    idList << -1 << 0 << 66 << -1 << -1 << -1 << -1 << -1;
    for(int i=0; i<8; ++i)
    {
        idList[1] = i;
        controls.push_back(new ValueControl("TriState button " + QString::number(i), ValueControl::Track | ValueControl::Voice | ValueControl::Note | ValueControl::Amount | ValueControl::Number | ValueControl::Value | ValueControl::Numerator | ValueControl::Denominator, ValueControl::Velocity, idList, 0, 0, QList<int>()));
    }

    // Number buttons left of tristate buttons
    idList.clear();
    idList << -1 << 0 << 50 << 127 << -1 << -1 << -1 << -1 << -1;
    for(int i=0; i<8; ++i)
    {
        idList[1] = i;
        controls.push_back(new ValueControl("Number button " + QString::number(i), ValueControl::Track | ValueControl::Voice | ValueControl::Note | ValueControl::Velocity | ValueControl::Amount | ValueControl::Number | ValueControl::Value | ValueControl::Numerator | ValueControl::Denominator, ValueControl::Type, idList, 0, 0, QList<int>()));
    }

    // S buttons below number buttons
    idList[2] = 49;
    for(int i=0; i<8; ++i)
    {
        idList[1] = i;
        controls.push_back(new ValueControl("S button " + QString::number(i), ValueControl::Track | ValueControl::Voice | ValueControl::Note | ValueControl::Velocity | ValueControl::Amount | ValueControl::Number | ValueControl::Value | ValueControl::Numerator | ValueControl::Denominator, ValueControl::Type, idList, 0, 0, QList<int>()));
    }

    // rec / circle buttons below tristate A|B buttons
    idList[2] = 48;
    for(int i=0; i<8; ++i)
    {
        idList[1] = i;
        controls.push_back(new ValueControl("Rec button " + QString::number(i), ValueControl::Track | ValueControl::Voice | ValueControl::Note | ValueControl::Velocity | ValueControl::Amount | ValueControl::Number | ValueControl::Value | ValueControl::Numerator | ValueControl::Denominator, ValueControl::Type, idList, 0, 0, QList<int>()));
    }

    // Other controls
    idList.clear();
    idList << -1 << 0 << 97 << 127 << -1 << -1 << -1 << -1 << -1;
    controls.push_back(new ValueControl("Bank select left button", ValueControl::Track | ValueControl::Voice | ValueControl::Note | ValueControl::Velocity | ValueControl::Amount | ValueControl::Number | ValueControl::Value | ValueControl::Numerator | ValueControl::Denominator, ValueControl::Type, idList, 0, 0, QList<int>()));
    idList[2] = 94;
    controls.push_back(new ValueControl("Bank select top button", ValueControl::Track | ValueControl::Voice | ValueControl::Note | ValueControl::Velocity | ValueControl::Amount | ValueControl::Number | ValueControl::Value | ValueControl::Numerator | ValueControl::Denominator, ValueControl::Type, idList, 0, 0, QList<int>()));
    idList[2] = 96;
    controls.push_back(new ValueControl("Bank select right button", ValueControl::Track | ValueControl::Voice | ValueControl::Note | ValueControl::Velocity | ValueControl::Amount | ValueControl::Number | ValueControl::Value | ValueControl::Numerator | ValueControl::Denominator, ValueControl::Type, idList, 0, 0, QList<int>()));
    idList[2] = 95;
    controls.push_back(new ValueControl("Bank select bottom button", ValueControl::Track | ValueControl::Voice | ValueControl::Note | ValueControl::Velocity | ValueControl::Amount | ValueControl::Number | ValueControl::Value | ValueControl::Numerator | ValueControl::Denominator, ValueControl::Type, idList, 0, 0, QList<int>()));
    idList[2] = 98;
    controls.push_back(new ValueControl("Shift button", ValueControl::Track | ValueControl::Voice | ValueControl::Note | ValueControl::Velocity | ValueControl::Amount | ValueControl::Number | ValueControl::Value | ValueControl::Numerator | ValueControl::Denominator, ValueControl::Type, idList, 0, 0, QList<int>()));
    idList[2] = 103;
    controls.push_back(new ValueControl("Bank button", ValueControl::Track | ValueControl::Voice | ValueControl::Note | ValueControl::Velocity | ValueControl::Amount | ValueControl::Number | ValueControl::Value | ValueControl::Numerator | ValueControl::Denominator, ValueControl::Type, idList, 0, 0, QList<int>()));
    idList[2] = 65;
    controls.push_back(new ValueControl("Detail view button", ValueControl::Track | ValueControl::Voice | ValueControl::Note | ValueControl::Velocity | ValueControl::Amount | ValueControl::Number | ValueControl::Value | ValueControl::Numerator | ValueControl::Denominator, ValueControl::Type, idList, 0, 0, QList<int>()));
    idList[2] = 64;
    controls.push_back(new ValueControl("Clip/dev. view button", ValueControl::Track | ValueControl::Voice | ValueControl::Note | ValueControl::Velocity | ValueControl::Amount | ValueControl::Number | ValueControl::Value | ValueControl::Numerator | ValueControl::Denominator, ValueControl::Type, idList, 0, 0, QList<int>()));
    idList[2] = 63;
    controls.push_back(new ValueControl("Dev. lock button", ValueControl::Track | ValueControl::Voice | ValueControl::Note | ValueControl::Velocity | ValueControl::Amount | ValueControl::Number | ValueControl::Value | ValueControl::Numerator | ValueControl::Denominator, ValueControl::Type, idList, 0, 0, QList<int>()));
    idList[2] = 62;
    controls.push_back(new ValueControl("Dev. on/off button", ValueControl::Track | ValueControl::Voice | ValueControl::Note | ValueControl::Velocity | ValueControl::Amount | ValueControl::Number | ValueControl::Value | ValueControl::Numerator | ValueControl::Denominator, ValueControl::Type, idList, 0, 0, QList<int>()));
    idList[2] = 61;
    controls.push_back(new ValueControl("Bank right arrow button", ValueControl::Track | ValueControl::Voice | ValueControl::Note | ValueControl::Velocity | ValueControl::Amount | ValueControl::Number | ValueControl::Value | ValueControl::Numerator | ValueControl::Denominator, ValueControl::Type, idList, 0, 0, QList<int>()));
    idList[2] = 60;
    controls.push_back(new ValueControl("Bank left arrow button", ValueControl::Track | ValueControl::Voice | ValueControl::Note | ValueControl::Velocity | ValueControl::Amount | ValueControl::Number | ValueControl::Value | ValueControl::Numerator | ValueControl::Denominator, ValueControl::Type, idList, 0, 0, QList<int>()));
    idList[2] = 59;
    controls.push_back(new ValueControl("Device right arrow button", ValueControl::Track | ValueControl::Voice | ValueControl::Note | ValueControl::Velocity | ValueControl::Amount | ValueControl::Number | ValueControl::Value | ValueControl::Numerator | ValueControl::Denominator, ValueControl::Type, idList, 0, 0, QList<int>()));
    idList[2] = 58;
    controls.push_back(new ValueControl("Device left arrow button", ValueControl::Track | ValueControl::Voice | ValueControl::Note | ValueControl::Velocity | ValueControl::Amount | ValueControl::Number | ValueControl::Value | ValueControl::Numerator | ValueControl::Denominator, ValueControl::Type, idList, 0, 0, QList<int>()));
    idList[2] = 101;
    controls.push_back(new ValueControl("Nudge + button", ValueControl::Track | ValueControl::Voice | ValueControl::Note | ValueControl::Velocity | ValueControl::Amount | ValueControl::Number | ValueControl::Value | ValueControl::Numerator | ValueControl::Denominator, ValueControl::Type, idList, 0, 0, QList<int>()));
    idList[2] = 100;
    controls.push_back(new ValueControl("Nudge - button", ValueControl::Track | ValueControl::Voice | ValueControl::Note | ValueControl::Velocity | ValueControl::Amount | ValueControl::Number | ValueControl::Value | ValueControl::Numerator | ValueControl::Denominator, ValueControl::Type, idList, 0, 0, QList<int>()));
    idList[2] = 89;
    controls.push_back(new ValueControl("User button", ValueControl::Track | ValueControl::Voice | ValueControl::Note | ValueControl::Velocity | ValueControl::Amount | ValueControl::Number | ValueControl::Value | ValueControl::Numerator | ValueControl::Denominator, ValueControl::Type, idList, 0, 0, QList<int>()));
    idList[2] = 99;
    controls.push_back(new ValueControl("Tap Tempo button", ValueControl::Track | ValueControl::Voice | ValueControl::Note | ValueControl::Velocity | ValueControl::Amount | ValueControl::Number | ValueControl::Value | ValueControl::Numerator | ValueControl::Denominator, ValueControl::Type, idList, 0, 0, QList<int>()));
    idList[2] = 90;
    controls.push_back(new ValueControl("Metronome button", ValueControl::Track | ValueControl::Voice | ValueControl::Note | ValueControl::Velocity | ValueControl::Amount | ValueControl::Number | ValueControl::Value | ValueControl::Numerator | ValueControl::Denominator, ValueControl::Type, idList, 0, 0, QList<int>()));
    idList[2] = 88;
    controls.push_back(new ValueControl("Sends button", ValueControl::Track | ValueControl::Voice | ValueControl::Note | ValueControl::Velocity | ValueControl::Amount | ValueControl::Number | ValueControl::Value | ValueControl::Numerator | ValueControl::Denominator, ValueControl::Type, idList, 0, 0, QList<int>()));
    idList[2] = 87;
    controls.push_back(new ValueControl("Pan button", ValueControl::Track | ValueControl::Voice | ValueControl::Note | ValueControl::Velocity | ValueControl::Amount | ValueControl::Number | ValueControl::Value | ValueControl::Numerator | ValueControl::Denominator, ValueControl::Type, idList, 0, 0, QList<int>()));
    idList[2] = 91;
    controls.push_back(new ValueControl("Play button", ValueControl::Track | ValueControl::Voice | ValueControl::Note | ValueControl::Velocity | ValueControl::Amount | ValueControl::Number | ValueControl::Value | ValueControl::Numerator | ValueControl::Denominator, ValueControl::Type, idList, 0, 0, QList<int>()));
    idList[2] = 93;
    controls.push_back(new ValueControl("Record button", ValueControl::Track | ValueControl::Voice | ValueControl::Note | ValueControl::Velocity | ValueControl::Amount | ValueControl::Number | ValueControl::Value | ValueControl::Numerator | ValueControl::Denominator, ValueControl::Type, idList, 0, 0, QList<int>()));
    idList[2] = 102;
    controls.push_back(new ValueControl("Session button", ValueControl::Track | ValueControl::Voice | ValueControl::Note | ValueControl::Velocity | ValueControl::Amount | ValueControl::Number | ValueControl::Value | ValueControl::Numerator | ValueControl::Denominator, ValueControl::Type, idList, 0, 0, QList<int>()));

    // Cue Level knob
    idList.clear();
    idList << -1 << 0 << -1 << -1 << -1 << 47 << -1 << -1 << 4;
    controls.push_back(new ValueControl("Cue level knob", ValueControl::Track | ValueControl::Voice | ValueControl::Note | ValueControl::Velocity | ValueControl::Amount | ValueControl::Number | ValueControl::Numerator | ValueControl::Denominator | ValueControl::Type, ValueControl::Value, idList, 0, 0, QList<int>(), true));

    // Tempo knob
    idList.clear();
    idList << -1 << 0 << -1 << -1 << -1 << 13 << -1 << -1 << 4;
    controls.push_back(new ValueControl("Tempo knob", ValueControl::Track | ValueControl::Voice | ValueControl::Note | ValueControl::Velocity | ValueControl::Amount | ValueControl::Number | ValueControl::Numerator | ValueControl::Denominator | ValueControl::Type, ValueControl::Value, idList, 0, 0, QList<int>(), true));

    for(int i=0; i<controls.size(); ++i)
        QObject::connect(controls.at(i),&ValueControl::updateOutputs, this, &AkaiAPC40MkII::updateControlOutputs);

    colors << QColor("#000000")
        << QColor("#1E1E1E")
        << QColor("#7F7F7F")
        << QColor("#FFFFFF")
        << QColor("#FF4C4C")
        << QColor("#FF0000")
        << QColor("#590000")
        << QColor("#190000")
        << QColor("#FFBD6C")
        << QColor("#FF5400")
        << QColor("#591D00")
        << QColor("#271B00")
        << QColor("#FFFF4C")
        << QColor("#FFFF00")
        << QColor("#595900")
        << QColor("#191900")
        << QColor("#88FF4C")
        << QColor("#54FF00")
        << QColor("#1D5900")
        << QColor("#142B00")
        << QColor("#4CFF4C")
        << QColor("#00FF00")
        << QColor("#005900")
        << QColor("#001900")
        << QColor("#4CFF5E")
        << QColor("#00FF19")
        << QColor("#00590D")
        << QColor("#001902")
        << QColor("#4CFF88")
        << QColor("#00FF55")
        << QColor("#00591D")
        << QColor("#001F12")
        << QColor("#4CFFB7")
        << QColor("#00FF99")
        << QColor("#005935")
        << QColor("#001912")
        << QColor("#4CC3FF")
        << QColor("#00A9FF")
        << QColor("#004152")
        << QColor("#001019")
        << QColor("#4C88FF")
        << QColor("#0055FF")
        << QColor("#001D59")
        << QColor("#000819")
        << QColor("#4C4CFF")
        << QColor("#0000FF")
        << QColor("#000059")
        << QColor("#000019")
        << QColor("#874CFF")
        << QColor("#5400FF")
        << QColor("#190064")
        << QColor("#0F0030")
        << QColor("#FF4CFF")
        << QColor("#FF00FF")
        << QColor("#590059")
        << QColor("#190019")
        << QColor("#FF4C87")
        << QColor("#FF0054")
        << QColor("#59001D")
        << QColor("#220013")
        << QColor("#FF1500")
        << QColor("#993500")
        << QColor("#795100")
        << QColor("#436400")
        << QColor("#033900")
        << QColor("#005735")
        << QColor("#00547F")
        << QColor("#0000FF")
        << QColor("#00454F")
        << QColor("#2500CC")
        << QColor("#7F7F7F")
        << QColor("#202020")
        << QColor("#FF0000")
        << QColor("#BDFF2D")
        << QColor("#AFED06")
        << QColor("#64FF09")
        << QColor("#108B00")
        << QColor("#00FF87")
        << QColor("#00A9FF")
        << QColor("#002AFF")
        << QColor("#3F00FF")
        << QColor("#7A00FF")
        << QColor("#B21A7D")
        << QColor("#402100")
        << QColor("#FF4A00")
        << QColor("#88E106")
        << QColor("#72FF15")
        << QColor("#00FF00")
        << QColor("#3BFF26")
        << QColor("#59FF71")
        << QColor("#38FFCC")
        << QColor("#5B8AFF")
        << QColor("#3151C6")
        << QColor("#877FE9")
        << QColor("#D31DFF")
        << QColor("#FF005D")
        << QColor("#FF7F00")
        << QColor("#B9B000")
        << QColor("#90FF00")
        << QColor("#835D07")
        << QColor("#392b00")
        << QColor("#144C10")
        << QColor("#0D5038")
        << QColor("#15152A")
        << QColor("#16205A")
        << QColor("#693C1C")
        << QColor("#A8000A")
        << QColor("#DE513D")
        << QColor("#D86A1C")
        << QColor("#FFE126")
        << QColor("#9EE12F")
        << QColor("#67B50F")
        << QColor("#1E1E30")
        << QColor("#DCFF6B")
        << QColor("#80FFBD")
        << QColor("#9A99FF")
        << QColor("#8E66FF")
        << QColor("#404040")
        << QColor("#757575")
        << QColor("#E0FFFF")
        << QColor("#A00000")
        << QColor("#350000")
        << QColor("#1AD000")
        << QColor("#074200")
        << QColor("#B9B000")
        << QColor("#3F3100")
        << QColor("#B35F00")
        << QColor("#4B1502");

    for(int a = 0; a < 100; ++a)
    for(int i=0; i<8; ++i)
        for(int j=0; j<5; ++j)
        {
            lightMatrix(i, j, QColor::fromRgbF(.5+.5*cos(.1*a+i),.5+.5*cos(.1*a+j+2.),.5+.5*cos(.1*a+i+4.)));
        }
}

AkaiAPC40MkII::~AkaiAPC40MkII()
{
    for(int i=0; i<8; ++i)
        for(int j=0; j<5; ++j)
        {
            lightMatrix(i, j, Qt::black);
        }
}

int AkaiAPC40MkII::codeFromColor(QColor color)
{
    float mostSimiliarDistance = 100.,
        distance;
    int mostSimiliarIndex = 0;
    for(int i=0; i<colors.size(); ++i)
    {
        QColor testColor = colors.at(i);
        distance = sqrtf(
            powf(color.red()-testColor.red(),2.)
            + powf(color.green()-testColor.green(),2.)
            + powf(color.blue()-testColor.blue(),2.)
        );
        if(distance < mostSimiliarDistance)
        {
            mostSimiliarDistance = distance;
            mostSimiliarIndex = i;
        }
    }
    return mostSimiliarIndex;
}

QColor AkaiAPC40MkII::colorFromCode(int index)
{
    return colors.at(index);
}

void AkaiAPC40MkII::lightMatrix(int x, int y, QColor color)
{
    if(x>7) return;
    if(y>4) return;
    if(x<0) return;
    if(y<0) return;

    ValueControl *button = control(MatrixButton, matrixOffset(x,y));
    QMidiEvent event = button->setValue(codeFromColor(color));
    midiOut->sendEvent(event);
    emit matrixLit(x,y,color);
}

void AkaiAPC40MkII::lightSceneLaunchButton(int y, QColor color)
{
    if(y<0) return;
    if(y>4) return;

    ValueControl *button = control(SceneLaunchButton, y);
    QMidiEvent event = button->setValue(codeFromColor(color));
    midiOut->sendEvent(event);
    emit sceneLaunchButtonLit(y, color);
}

ValueControl *AkaiAPC40MkII::control(ControlType type, int offset)
{
    return controls.at((int)type + offset);
}

int AkaiAPC40MkII::matrixOffset(int x, int y)
{
    return y * 8 + x;
}

int AkaiAPC40MkII::bankOffset(int bank, int knob)
{
    return bank * 8 + knob;
}

void AkaiAPC40MkII::updateControlOutputs(ValueControl *sender, int newValue)
{
    QMidiEvent event = sender->setValue(newValue);
    midiOut->sendEvent(event);
}
