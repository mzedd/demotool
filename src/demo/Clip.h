#ifndef CLIP_H
#define CLIP_H

#include <QString>
#include "../scene/Scene.h"
#include "../scene/Camera.h"
#include "timelineitem.h"

class Clip
{
private:
    Scene* scene;
    Camera* camera;
    float duration;
    QString name;
public:
    Clip();
    void attachScene(Scene *scene);
    void attachCamera(int cameraNumber);
    void setDuration(const float duration);
    float getDuration();
    void render(float time) const;
    QString getName() const;
    Scene* getScene() const;
    Camera &getCamera();
    void setName(const QString name);
};

#endif // CLIP_H
