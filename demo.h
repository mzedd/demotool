#ifndef DEMO_H
#define DEMO_H

#include <QOpenGLShaderProgram>
#include "scene/Scene.h"

class Demo
{
private:
    std::vector<Scene> sceneList;
    std::vector<QOpenGLShaderProgram> shaderList;
public:
    Demo();
};

#endif // DEMO_H
