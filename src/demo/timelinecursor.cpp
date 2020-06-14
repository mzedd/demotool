#include "timelinecursor.h"

#include <QEvent>
#include <QDebug>
#include <QPainter>

TimelineCursor::TimelineCursor(QWidget *parent)
    : QWidget(parent)
{
}

float TimelineCursor::getPosition()
{
    return pos().x();
}

void TimelineCursor::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.setBrush(Qt::black);

    painter.drawRect(QRect(0, 0, 20, 100));

}

void TimelineCursor::mousePressEvent(QMouseEvent *event) {
    qDebug() << "Mouse Pressed";
}

void TimelineCursor::enterEvent(QEvent *event)
{
    qDebug() << "Enter";

    setCursor(Qt::CursorShape::SizeHorCursor);

    QWidget::enterEvent(event);
}

void TimelineCursor::leaveEvent(QEvent *event)
{
    qDebug() << "Leave";
    setCursor(Qt::CursorShape::ArrowCursor);

    QWidget::leaveEvent(event);
}
