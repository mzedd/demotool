#include "ShaderOnlyScene.h"

ShaderOnlyScene::ShaderOnlyScene() :
    ShaderOnlyScene(nullptr)
{

}

ShaderOnlyScene::ShaderOnlyScene(QOpenGLShaderProgram *shader) :
    shader(shader)
{
    float vertices[] = {
        -1.0f, -1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
         1.0f,  1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
         1.0f,  1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f
    };
    int vertexLocation = shader->attributeLocation("vertex");
    shader->enableAttributeArray(vertexLocation);
    shader->setAttributeArray(vertexLocation, vertices, 3);
}

void ShaderOnlyScene::renderAt(float time)
{
    shader->setUniformValue("iTime", time);
    shader->bind();
}

void ShaderOnlyScene::setShader(QOpenGLShaderProgram *shader)
{
    this->shader = shader;
}
