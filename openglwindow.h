#ifndef OPENGLWINDOW_H
#define OPENGLWINDOW_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QTime>

#include "demo.h"

class Clip;

class OpenGLWindow : public QOpenGLWidget, protected QOpenGLFunctions
{
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
};

#endif // OPENGLWINDOW_H
