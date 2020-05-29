#ifndef DEMO_H
#define DEMO_H

#include <QOpenGLShaderProgram>
#include "demo/Timeline.h"
#include "scene/Scene.h"

class Demo
{
private:
    Timeline timeline;
    std::vector<Scene> sceneList;
    std::vector<QOpenGLShaderProgram> shaderList;
public:
    Demo();
};

#endif // DEMO_H
