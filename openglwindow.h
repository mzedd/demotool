#ifndef OPENGLWINDOW_H
#define OPENGLWINDOW_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QTime>

#include "scene/Camera.h"


class OpenGLWindow : public QOpenGLWidget, protected QOpenGLFunctions
{
private:
    Camera camera;
    QOpenGLVertexArrayObject vao;
    QOpenGLBuffer vbo;
    QOpenGLBuffer ebo;

    QOpenGLShaderProgram *program;

    QMatrix4x4 view;
    QMatrix4x4 projection;

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

    void keyPressEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
};

#endif // OPENGLWINDOW_H
