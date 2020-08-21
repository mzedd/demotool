#include "openglwindow.h"

#include <QOpenGLShader>
#include "src/demo/Clip.h"

#include <QtMath>
#include <QTime>

OpenGLWindow::OpenGLWindow(QWidget *parent) :
    QOpenGLWidget(parent),
    currentClip(nullptr),
    demoTime(0.0f)
{
    run = false;
    setFocusPolicy(Qt::StrongFocus);
    timer.start();
}

OpenGLWindow::~OpenGLWindow() {
    makeCurrent();
}

void OpenGLWindow::initializeGL() {
    makeCurrent();
    initializeOpenGLFunctions();

    Scene* scene = Demo::instance().addScene();

    // testing
    Clip *clip = Demo::instance().addClip();
    clip->setName("Erster");
    clip->setDuration(50.0f);
    clip->attachScene(scene);

    currentClip = clip;

    glViewport(0, 0, width(), height());
}

void OpenGLWindow::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);

    viewportSize = QVector2D(w, h);

    qDebug() << viewportSize;

    if(currentClip) {
        currentClip->getScene()->setViewportResolution(viewportSize);
    }
}

void OpenGLWindow::paintGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(run) {
        float currentTime = static_cast<float>(timer.elapsed()) * 0.001f;
        demoTime += (currentTime - lastFrameTime);
        emit timeChanged(demoTime);
        lastFrameTime = currentTime;
        qDebug() << demoTime << " current time" << currentTime << "lastFramTime: " << lastFrameTime;
    }

    if(currentClip) {
        qDebug() << "Clip name: " << currentClip->getName();
        currentClip->render(demoTime);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        qDebug() << "clip renderd";
    }

    if(run) {
        update();
    }
}

void OpenGLWindow::clipSelectionChanged(Clip *clip)
{
    qDebug() << "current clip changed";

    currentClip = clip;
    currentClip->getScene()->setViewportResolution(viewportSize);

    update();
}

void OpenGLWindow::togglePlay()
{
    run = !run;
    lastFrameTime = static_cast<float>(timer.elapsed()) * 0.001f;
    update();
    qDebug() << "called";
}

void OpenGLWindow::cursorChanged(float time)
{
    demoTime = time;
    update();
}
