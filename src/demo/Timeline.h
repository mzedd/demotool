#ifndef TIMELINE_H
#define TIMELINE_H

#include <QWidget>
#include <QWheelEvent>
#include <vector>

#include "Clip.h"

class Timeline : public QWidget
{
    Q_OBJECT
private:
    std::vector<Clip> clipList;
    // track
    // post procesing
    float mouseAttachment;
public:
    explicit Timeline(QWidget *paren = nullptr);
    float zoom;
    float offset;
    Clip* highlightedClip;
protected:
    void paintEvent(QPaintEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
private slots:
    void zoomChanged(int zoom);
};

#endif // TIMELINE_H
