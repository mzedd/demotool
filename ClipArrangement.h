#ifndef CLIPARRANGEMENT_H
#define CLIPARRANGEMENT_H

#include <QWidget>

class TimelineModel;

namespace Ui {
class ClipArrangement;
}

class ClipArrangement : public QWidget
{
    Q_OBJECT

public:
    explicit ClipArrangement(QWidget *parent = nullptr);
    ~ClipArrangement();

private:
    Ui::ClipArrangement *ui;
    TimelineModel *model;
};

#endif // CLIPARRANGEMENT_H
