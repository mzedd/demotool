#include "openglwindow.h"

#include <QOpenGLShader>
#include "src/demo/Clip.h"
#include "src/scene/SceneObject.h"
#include "src/modelling/Plane.h"

#include <QtMath>

OpenGLWindow::OpenGLWindow(QWidget *parent) :
    QOpenGLWidget(parent),
    currentClip(nullptr),
    lastFrameTime(0.0f),
    deltaTime(0.0f)
{
    setFocusPolicy(Qt::StrongFocus);
    timer.start();
}

OpenGLWindow::~OpenGLWindow() {
    makeCurrent();
}

void OpenGLWindow::initializeGL() {
    makeCurrent();
    initializeOpenGLFunctions();
}

void OpenGLWindow::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);

    if(currentClip) {
        currentClip->getCamera().updateProjectionMatrix(w, h);
    }
}

void OpenGLWindow::paintGL() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    float currentTime = static_cast<float>(timer.elapsed()) * 0.001f;
    deltaTime = currentTime - lastFrameTime;
    lastFrameTime = currentTime;

    if(currentClip)
        currentClip->render(currentTime);
}
