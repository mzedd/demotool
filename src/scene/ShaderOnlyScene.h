#ifndef SHADERONLYSCENE_H
#define SHADERONLYSCENE_H

#include <scene/Scene.h>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>

class ShaderOnlyScene : public Scene
{
private:
    QOpenGLShaderProgram* shader;
public:
    ShaderOnlyScene();
    ShaderOnlyScene(QOpenGLShaderProgram* shader);
    void renderAt(float time);
    void setShader(QOpenGLShaderProgram* shader);
};

#endif // SHADERONLYSCENE_H
