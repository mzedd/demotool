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

    qDebug() << shaderList.size();

    return shaderProgram;
}

Scene *Demo::getScenePointer(int id)
{
    return &sceneList[id];
}

void Demo::addClip()
{
    clipList.push_back(Clip());
}

Clip &Demo::getClip(int id)
{
    return clipList[id];
}

bool Demo::removeClips(int id, int count) {
    if(id+count < clipCount()) {
        clipList.erase(clipList.begin()+id, clipList.begin()+id+count);
        return true;
    }
    return false;
}

const size_t Demo::clipCount() const
{
    return clipList.size();
}

bool Demo::swapClips(int idA, int idB)
{
    if(idA < clipCount() && idB < clipCount()) {
        Clip tmp = clipList[idA];
        clipList[idA] = clipList[idB];
        clipList[idB] = clipList[idA];
        return true;
    }
    return false;
}

QOpenGLShaderProgram &Demo::getShaderProgram(int id)
{
    return *shaderList[id];
}
