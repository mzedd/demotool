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

    QOpenGLShaderProgram *program = Demo::instance().addShader("data/shader/quad.vert", "data/shader/voronoi.frag");
    program->setObjectName("default shader");
    Scene* scene = Demo::instance().addScene(program);

    // testing
    Clip *clip = Demo::instance().addClip();
    clip->setName("Erster");
    clip->setDuration(50.0f);
    clip->attachScene(scene);

    glViewport(0, 0, width(), height());
}

void OpenGLWindow::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);

    Demo::instance().getShaderProgram(0).bind();
    Demo::instance().getShaderProgram(0).setUniformValue("iResolution", QVector2D(w,h));
}

void OpenGLWindow::paintGL() {
    glClearColor(.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(run) {
        float currentTime = static_cast<float>(timer.elapsed()) * 0.001f;
        demoTime += (currentTime - lastFrameTime);
        emit timeChanged(demoTime);
        lastFrameTime = currentTime;
        qDebug() << demoTime << " current time" << currentTime << "lastFramTime: " << lastFrameTime;
    }


    if(currentClip) {
        currentClip->render(demoTime/currentClip->getDuration());
        glDrawArrays(GL_TRIANGLES, 0, 6);
        qDebug() << "clip renderd";
    }

    qDebug() << "run";

    if(run) {
        update();
    }
}

void OpenGLWindow::clipSelectionChanged(Clip *clip)
{
    qDebug() << "current clip changed";

    currentClip = clip;

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
