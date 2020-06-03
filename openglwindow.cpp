#include "openglwindow.h"

#include <QOpenGLShader>
#include <iostream>

#include <QtMath>

OpenGLWindow::OpenGLWindow(QWidget *parent) :
    QOpenGLWidget(parent),
    camera(QVector3D(0.0, 0.0, 5.0), QVector3D(0.0, 0.0, -1.0), QVector3D(0.0, 1.0, 0.0), 1.0),
    vao(0),
    vbo(QOpenGLBuffer(QOpenGLBuffer::Type::VertexBuffer)),
    ebo(QOpenGLBuffer(QOpenGLBuffer::Type::IndexBuffer)),
    program(0)
{
    setFocusPolicy(Qt::StrongFocus);
    timer.start();
}

OpenGLWindow::~OpenGLWindow() {
    makeCurrent();

    ebo.destroy();
    vao.destroy();
    vbo.destroy();
}

void OpenGLWindow::initializeGL() {
    initializeOpenGLFunctions();

    glEnable(GL_DEPTH_TEST);

    vao.create();
    vbo.create();
    ebo.create();

    float vertices[] = {
         0.0f, sqrt(6.0f)*0.25f, 0.0f,
         0.0f, -1.0f / sqrt(24.0f), -sqrt(3.0f)/3.0f,
        -0.5f, -1.0f / sqrt(24.0f), 0.5f / sqrt(3.0f),
         0.5f, -1.0f / sqrt(24.0f), 0.5f / sqrt(3.0f)
    };

    unsigned int elements[] = {
        0, 1, 3,
        0, 3, 2,
        0, 2, 1,
        1, 2, 3
    };

    vao.bind();
    vbo.bind();
    vbo.allocate(vertices, sizeof(vertices));
    ebo.bind();
    ebo.allocate(elements, sizeof(elements));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    QOpenGLShader vertShader(QOpenGLShader::Vertex);
    QOpenGLShader fragShader(QOpenGLShader::Fragment);

    QString file("data/shader/shader.vert");
    vertShader.compileSourceFile(file);
    file = QString("data/shader/shader.frag");
    fragShader.compileSourceFile(file);

    program = new QOpenGLShaderProgram();
    program->addShader(&vertShader);
    program->addShader(&fragShader);
    program->link();

}

void OpenGLWindow::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
    projection.setToIdentity();
    projection.perspective(45.0f, w/float(h), 0.1f, 100.0f);

}

void OpenGLWindow::paintGL() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    deltaTime = timer.elapsed() * 0.001f - lastFrameTime;
    lastFrameTime = timer.elapsed() * 0.001f;

    view = camera.getViewMatrix();

    program->bind();
    program->setUniformValue(program->uniformLocation("model"), QMatrix4x4());
    program->setUniformValue(program->uniformLocation("view"), view);
    program->setUniformValue(program->uniformLocation("projection"), projection);

    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

}

void OpenGLWindow::keyPressEvent(QKeyEvent *event) {
    switch(event->key()) {
        case Qt::Key::Key_W:
        camera.position += camera.front*0.1f;
        break;
    case Qt::Key_S:
        camera.position -= camera.front*0.1f;
        break;
    case Qt::Key_A:
        camera.position -= camera.getRight()*camera.speed*deltaTime;
        break;
    case Qt::Key_D:
        camera.position += camera.getRight()*camera.speed*deltaTime;
        break;
    }
    update();
}

void OpenGLWindow::mousePressEvent(QMouseEvent *event) {
    switch(event->button()) {
    case Qt::MouseButton::LeftButton:
        std::cout << "moin" << std::endl;
        break;
    default:
        break;
    }
}

void OpenGLWindow::mouseReleaseEvent(QMouseEvent *event) {
    switch(event->button()) {
    case Qt::MouseButton::LeftButton:
        camera.firstMouse = true;
        break;
    default:
        break;
    }
}

void OpenGLWindow::mouseMoveEvent(QMouseEvent *event) {
    camera.updateFront(event->x(), event->y());
    update();
}
