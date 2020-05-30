#ifndef CLIP_H
#define CLIP_H

#include "../scene/Scene.h"
#include "../scene/Camera.h"

class Clip
{
private:
    Scene* scene;
    Camera* camera;
    float duration;
public:
    Clip();
    void attachScene(Scene& scene);
    void attachCamera(int cameraNumber);
    void setDuration(const float duration);
    float getDuration();
};

#endif // CLIP_H
