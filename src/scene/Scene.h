#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <scene/Camera.h>

class Scene {
protected:
    std::vector<Camera> cameraList;
public:
    virtual void renderAt(float time) = 0;
    virtual ~Scene() {};
};

#endif // SCENE_H
