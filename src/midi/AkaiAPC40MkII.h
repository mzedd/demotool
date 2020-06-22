#pragma once

#include "MidiController.h"

class AkaiAPC40MkII : public MidiController
{
    public:
    AkaiAPC40MkII(QString key, QString name, int type);
    virtual ~AkaiAPC40MkII();
    QColor colorFromCode(int index);
    int codeFromColor(QColor color);

    private:
    QList<QColor> colors;
};