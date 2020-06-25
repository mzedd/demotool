#include "openglwindow.h"

#include <QOpenGLShader>
#include "src/demo/Clip.h"
#include "src/scene/SceneObject.h"
#include "src/modelling/Plane.h"

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

    QOpenGLShaderProgram *program = Demo::instance().addShader("data/shader/shader.vert", "data/shader/loading.frag");

    program->setObjectName("default shader");

    // testing
    Demo::instance().addClip();
    Clip &clip = Demo::instance().getClip(0);
    clip.setName("Erster");
    clip.setDuration(50.0f);

    Scene &scene = Demo::instance().addScene();
    Camera &camera = scene.addCamera();
    camera.position = QVector3D(1.0f, 1.0f, 5.0f);
    scene.name = "test";
    scene.setBackgroundColor(QVector3D(0.0f, 1.0f, 0.0f));
    scene.addLightSource();

    clip.attachScene(&scene);
    clip.attachCamera(0);

    SceneObject *plane = new SceneObject(new Plane(20, 10.0f, 10.0f), program);
    plane->geometry->generate();
    plane->transform.rotate(45.0f, Qt::Axis::XAxis);

    scene.addSceneObject(plane);

    glViewport(0, 0, width(), height());

    Demo::instance().getShaderProgram(0).setUniformValue("iResolution", QVector2D(width(),height()));

    if(currentClip) {
        currentClip->getCamera().updateProjectionMatrix(width(), height());
    }
}

void OpenGLWindow::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);

    Demo::instance().getShaderProgram(0).setUniformValue("iResolution", QVector2D(w,h));

    if(currentClip) {
        currentClip->getCamera().updateProjectionMatrix(w, h);
    }
}

void OpenGLWindow::paintGL() {
    //glClearColor(.0f, 0.0f, 0.0f, 1.0f);
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(run) {
        float currentTime = static_cast<float>(timer.elapsed()) * 0.001f;
        demoTime += (currentTime - lastFrameTime);
        emit timeChanged(demoTime);
        lastFrameTime = currentTime;
        qDebug() << demoTime << " current time" << currentTime << "lastFramTime: " << lastFrameTime;
    }


    if(currentClip) {
        currentClip->render(demoTime);
        qDebug() << "clip renderd";
    }

    qDebug() << "run";

    if(run) {
        update();
    }
}

void OpenGLWindow::clipSelectionChanged(Clip *clip)
{
    currentClip = clip;
    update();
}

void OpenGLWindow::togglePlay()
{
    run = !run;
    lastFrameTime = static_cast<float>(timer.elapsed()) * 0.001f;
    update();
}

void OpenGLWindow::cursorChanged(float time)
{
    demoTime = time;
    update();
}
