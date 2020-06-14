#ifndef TIMELINECURSOR_H
#define TIMELINECURSOR_H

#include <QWidget>

class TimelineCursor : public QWidget
{
    Q_OBJECT
public:
    explicit TimelineCursor(QWidget *parent = nullptr);
    float getPosition();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void enterEvent(QEvent* event) override;
    void leaveEvent(QEvent* event) override;

private:
    float position;
};

#endif // TIMELINECURSOR_H
