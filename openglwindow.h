#ifndef OPENGLWINDOW_H
#define OPENGLWINDOW_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QElapsedTimer>

#include "demo.h"

class Clip;

class OpenGLWindow : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
private:
    QElapsedTimer timer;
    Clip* currentClip;

    float lastFrameTime;
    float deltaTime;
    float demoTime;
    bool run;

public:
    OpenGLWindow(QWidget *parent);
    ~OpenGLWindow();

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

signals:
    void timeChanged(float time);

protected slots:
    void clipSelectionChanged(Clip *clip);
    void togglePlay();
    void cursorChanged(float time);
};

#endif // OPENGLWINDOW_H
