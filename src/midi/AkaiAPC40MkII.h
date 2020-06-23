#pragma once

#include "MidiController.h"

class AkaiAPC40MkII : public MidiController, QObject
{
    Q_OBJECT 

    public:
    AkaiAPC40MkII(QString inputKey, QString outputKey, QString name, int type);
    virtual ~AkaiAPC40MkII();
    QColor colorFromCode(int index);
    int codeFromColor(QColor color);
    void lightMatrix(int x, int y, QColor color);
    void lightSceneLaunchButton(int y, QColor color);
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
    ValueControl *numberButton(int x);
    ValueControl *sButton(int x);
    ValueControl *recButton(int x);
    ValueControl *bankSelectLeftButton();
    ValueControl *bankSelectTopButton();
    ValueControl *bankSelectRightButton();
    ValueControl *bankSelectBottomButton();
    ValueControl *shiftButton();
    ValueControl *bankButton();
    ValueControl *detailViewButton();
    ValueControl *clipDevViewButton();
    ValueControl *devLockButton();
    ValueControl *devOnOFfButton();
    ValueControl *bankRightArrowButton();
    ValueControl *bankLeftArrowButton();
    ValueControl *deviceRightArrowButton();
    ValueControl *deviceLeftArrowButton();
    ValueControl *nudgePlusButton();
    ValueControl *nudgeMinusButton();
    ValueControl *userButton();
    ValueControl *tapTempoButton();
    ValueControl *metronomeButton();
    ValueControl *sendsButton();
    ValueControl *panButton();
    ValueControl *playButton();
    ValueControl *recordButton();
    ValueControl *sessionButton();
    ValueControl *cueLevelKnob();
    ValueControl *TempoKnob();

    private slots:
    void updateControlOutputs(ValueControl *sender, int outputValue);

    signals:
    void matrixLit(int x, int y, QColor color);
    void sceneLaunchButtonLit(int y, QColor color);

    private:
    QList<QColor> colors;
};