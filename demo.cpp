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

size_t Demo::addShader()
{
    shaderList.push_back(new QOpenGLShaderProgram(0));
    return shaderList.size() - 1;
}

Scene *Demo::getScenePointer(int id)
{
    return &sceneList[id];
}

QOpenGLShaderProgram &Demo::getShaderPointer(int id)
{
    return *shaderList[id];
}
