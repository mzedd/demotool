#include "demo.h"

Demo::Demo()
{

}

Demo::~Demo()
{

}

Demo &Demo::instance()
{
    static Demo _instance;
    return _instance;
}

Scene &Demo::addScene()
{
    sceneList.push_back(Scene());

    return sceneList.back();
}

void Demo::addScene(Scene scene)
{
    sceneList.push_back(scene);
}

QOpenGLShaderProgram* Demo::addShader(const QString &vertShaderFile, const QString& fragShaderFile)
{
    QOpenGLShaderProgram* shaderProgram = new QOpenGLShaderProgram(0);

    // add and compile vertex shader
    QOpenGLShader vertShader(QOpenGLShader::Vertex);
    vertShader.compileSourceFile(vertShaderFile);

    if(!vertShader.isCompiled()) {
        qDebug() << vertShader.log();
        delete shaderProgram;
        return nullptr;
    }

    // add and compile fragment shader
    QOpenGLShader fragShader(QOpenGLShader::Fragment);
    fragShader.compileSourceFile(fragShaderFile);

    if(!fragShader.isCompiled()) {
        qDebug() << fragShader.log();
        delete shaderProgram;
        return nullptr;
    }

    // add and link shaders to program
    shaderProgram->addShader(&vertShader);
    shaderProgram->addShader(&fragShader);
    shaderProgram->link();

    if(!shaderProgram->isLinked()) {
        qDebug() << shaderProgram->log();
        delete shaderProgram;
        return nullptr;
    }

    // if all goes well add shader to list
    shaderList.push_back(shaderProgram);

    return shaderProgram;
}

Scene *Demo::getScenePointer(int id)
{
    return &sceneList[id];
}

QOpenGLShaderProgram &Demo::getShaderProgram(int id)
{
    return *shaderList[id];
}
