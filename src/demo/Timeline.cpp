#include "Timeline.h"

#include <QPainter>
#include <iostream>

Timeline::Timeline(QWidget *parent) :
    QWidget(parent)
{
    Clip clip = Clip("1");
    clip.setDuration(10.0f);
    clipList.push_back(clip);
    clip.setDuration(20.0f);
    clipList.push_back(clip);
    zoom = 1.0f;
    offset = 0.0f;

    highlightedClip = &clipList[1];
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
    for(std::vector<Clip>::iterator it = clipList.begin(); it != clipList.end(); it++) {
        clip.setWidth(it->getDuration()*zoom);
        painter.drawRect(clip);
    }

    if(highlightedClip != nullptr) {
        QPen pen(Qt::black);
        pen.setWidth(2);
        painter.setPen(pen);
        clip.setWidth(highlightedClip->getDuration()*zoom);
        painter.drawRect(clip);
    }
}

void Timeline::zoomChanged(int zoom) {
    this->zoom = zoom/100.0f;
    repaint();
}

void Timeline::wheelEvent(QWheelEvent *event) {
    offset += event->delta()*0.1f;
    repaint();
}

void Timeline::mousePressEvent(QMouseEvent *event) {
    bool selected = false;
    switch(event->button()) {
    case Qt::MouseButton::LeftButton:
        for(std::vector<Clip>::iterator it = clipList.begin(); it != clipList.end(); it++) {
            float y = 10.0f;
            float width = it->getDuration()*zoom;
            float height = 50.0f;

            if(event->x() >= x && event->x() <= x+width && event->y() >= y && event->y() <= y+height) {
                highlightedClip = &(*it);
                selected = true;
                repaint();
            }
        }

        if(!selected) {
            highlightedClip = nullptr;
            repaint();
        }
        break;

    default:
        break;
    }
}

void Timeline::mouseMoveEvent(QMouseEvent *event) {
    if(highlightedClip != nullptr) {
        repaint();
    }
}
