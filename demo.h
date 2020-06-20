#ifndef DEMO_H
#define DEMO_H

#include <QOpenGLShaderProgram>
#include "scene/Scene.h"

#include <QVector>

class Demo
{
private:
    std::vector<Scene> sceneList;
    std::vector<QOpenGLShaderProgram*> shaderList;

    Demo();
    ~Demo();

public:
    Demo(const Demo&) = delete;
    Demo(Demo&&) = delete;
    Demo& operator=(const Demo&) = delete;
    Demo& operator=(Demo&&) = delete;

    static Demo& instance();
    Scene& addScene();
    void addScene(Scene scene);
    size_t addShader();
    Scene* getScenePointer(int id);
    QOpenGLShaderProgram &getShaderPointer(int id);
};

#endif // DEMO_H
