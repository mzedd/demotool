#include "Timeline.h"

#include <QPainter>

Timeline::Timeline(QWidget *parent) :
    QWidget(parent)
{
    Clip clip = Clip();
    clip.setDuration(10.0f);
    clipList.push_back(clip);
    clip.setDuration(20.0f);
    clipList.push_back(clip);
}

void Timeline::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRectF size(10, 10, this->width()-10, this->width()-10);
    painter.setBrush(Qt::red);
    QRectF background(0,0, 200, 100);
    painter.drawRect(background);

    painter.setBrush(Qt::blue);

    QRectF clip = QRectF();
    clip.setY(10);
    clip.setHeight(50);
    float durationOffset = 0.0f;
    for(std::vector<Clip>::iterator it = clipList.begin(); it != clipList.end(); it++) {
        float duration = it->getDuration();
        clip.setX(durationOffset*zoom);
        clip.setWidth(duration*zoom);
        painter.drawRect(clip);
        durationOffset += duration + 5.0f;
    }



}

void Timeline::zoomChanged(int zoom) {
    this->zoom = zoom;
    repaint();
}
