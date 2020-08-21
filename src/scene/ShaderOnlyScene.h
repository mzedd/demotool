#ifndef SHADERONLYSCENE_H
#define SHADERONLYSCENE_H

#include <scene/Scene.h>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>

class ShaderOnlyScene : public Scene
{
private:
    QOpenGLShaderProgram shaderProgram;
    QOpenGLVertexArrayObject vao;
    QOpenGLBuffer vbo;
public:
    ShaderOnlyScene();
    void renderAt(float time);
    bool setShader(const QString& filename);
    void setViewportResolution(QVector2D resolution);
};

#endif // SHADERONLYSCENE_H
