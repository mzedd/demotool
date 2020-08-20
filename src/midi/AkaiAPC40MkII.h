#pragma once

#include "MidiController.h"

class AkaiAPC40MkII : public MidiController, QObject
{
    Q_OBJECT 

    public:
    typedef enum
    {
        Fader = 0,
        MasterFader = 8,
        HorizontalSlider = 9,
        BankKnob = 10,
        MasterBankKnob = 74,
        TopKnob = 82,
        MatrixButton = 90,
        SceneLaunchButton = 130,
        ClipStopButton = 135,
        TriStateButton = 143,
        NumberButton = 151,
        SButton = 159,
        RecButton = 167,
        BankSelectLeftButton = 185,
        BankSelectTopButton = 186,
        BankSelectRightButton = 187,
        BankSelectBottomButton = 188,
        ShiftButton = 189,
        BankButton = 190,
        DetailViewButton = 191,
        ClipDevViewButton = 192,
        DevLockButton = 193,
        DevOnOFfButton = 194,
        BankRightArrowButton = 195,
        BankLeftArrowButton = 196,
        DeviceRightArrowButton = 197,
        DeviceLeftArrowButton = 108,
        NudgePlusButton = 199,
        NudgeMinusButton = 200,
        UserButton = 201,
        TapTempoButton = 202,
        MetronomeButton = 203,
        SendsButton = 204,
        PanButton = 205,
        PlayButton = 206,
        RecordButton = 207,
        SessionButton = 208,
        CueLevelKnob = 209,
        TempoKnob = 210,
    } ControlType;

    AkaiAPC40MkII(QString inputKey, QString outputKey, QString name, int type);
    virtual ~AkaiAPC40MkII();
    QColor colorFromCode(int index);
    int codeFromColor(QColor color);
    void lightMatrix(int x, int y, QColor color);
    void lightSceneLaunchButton(int y, QColor color);
    ValueControl *control(ControlType type, int offset = 0);
    int matrixOffset(int x, int y);
    int bankOffset(int bank, int knob);

    private slots:
    void updateControlOutputs(ValueControl *sender, int outputValue);

    signals:
    void matrixLit(int x, int y, QColor color);
    void sceneLaunchButtonLit(int y, QColor color);

    private:
    QList<QColor> colors;
};