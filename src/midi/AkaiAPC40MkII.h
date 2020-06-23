#pragma once

#include "MidiController.h"

class AkaiAPC40MkII : public MidiController
{
    public:
    AkaiAPC40MkII(QString inputKey, QString outputKey, QString name, int type);
    virtual ~AkaiAPC40MkII();
    QColor colorFromCode(int index);
    int codeFromColor(QColor color);
    void lightMatrix(int x, int y, QColor color);
    void lightSceneLaunch(int y, QColor color);
    ValueControl *fader(int index);
    ValueControl *masterFader();
    ValueControl *horizontalSlider();
    ValueControl *bankKnob(int bank, int knob);
    ValueControl *masterBankKnob(int knob);
    ValueControl *topKnob(int knob);
    ValueControl *matrixButton(int x, int y);
    ValueControl *sceneLaunchButton(int y);
    ValueControl *clipStopButton(int x);
    ValueControl *triStateButton(int x);

    private:
    QList<QColor> colors;
};