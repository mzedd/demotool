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

protected:
    void keyPressEvent(QKeyEvent *event) override;

signals:
    void spacePressed();

private slots:
    void updateInspector();
    void updateTime(float time);
    void setClipDuration(const QString &text);
};

#endif // CLIPARRANGEMENT_H
