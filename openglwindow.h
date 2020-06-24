#ifndef OPENGLWINDOW_H
#define OPENGLWINDOW_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QTime>

#include "demo.h"

class Clip;

class OpenGLWindow : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
private:
    Clip* currentClip;

    QTime timer;
    float lastFrameTime;
    float deltaTime;

public:
    OpenGLWindow(QWidget *parent);
    ~OpenGLWindow();

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

protected slots:
    void clipSelectionChanged(Clip *clip);
};

#endif // OPENGLWINDOW_H
