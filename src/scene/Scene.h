#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <scene/Camera.h>
#include <QVector2D>

class Scene {
protected:
    std::vector<Camera> cameraList;
public:
    virtual ~Scene() {};
    virtual void renderAt(float time) = 0;
    virtual void setViewportResolution(QVector2D resolution) = 0;
};

#endif // SCENE_H
