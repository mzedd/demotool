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

private slots:
    void updateInspector();
    void updateTime(float time);
};

#endif // CLIPARRANGEMENT_H
