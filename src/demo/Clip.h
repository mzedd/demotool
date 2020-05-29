#ifndef CLIP_H
#define CLIP_H

#include "../scene/Scene.h"
#include "../scene/Camera.h"

class Clip
{
private:
    Scene* scene;
    Camera* camera;
public:
    Clip();
    void attachScene(Scene& scene);
    void attachCamera(int cameraNumber);
};

#endif // CLIP_H
