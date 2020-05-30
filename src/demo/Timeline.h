#ifndef TIMELINE_H
#define TIMELINE_H

#include <QWidget>
#include <vector>

#include "Clip.h"

class Timeline : public QWidget
{
    Q_OBJECT
private:
    std::vector<Clip> clipList;
    // track
    // post procesing
public:
    explicit Timeline(QWidget *paren = nullptr);
    float zoom;
protected:
    void paintEvent(QPaintEvent *event) override;
private slots:
    void zoomChanged(int zoom);
};

#endif // TIMELINE_H
