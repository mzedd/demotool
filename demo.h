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
    QOpenGLShaderProgram *addShader(const QString &vertShaderFile, const QString& fragShaderFile);
    Scene* getScenePointer(int id);
    QOpenGLShaderProgram &getShaderProgram(int id);
};

#endif // DEMO_H
