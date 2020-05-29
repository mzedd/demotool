#ifndef DEMO_H
#define DEMO_H

#include <vector>

#include "../Engine.h"
#include "Timeline.h"
#include "../scene/Scene.h"

class Demo
{
private:
    //Engine engine;
    Timeline timeline;
    std::vector<Scene> sceneList;
public:
    Demo();
    void exportToBinary();
};

#endif // DEMO_H
