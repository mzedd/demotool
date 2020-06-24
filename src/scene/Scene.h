#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <QVector3D>
#include <QString>

#include "SceneObject.h"
#include "Camera.h"
#include "light/ILightSource.h"

class Scene
{
private:
    std::vector<SceneObject*> sceneObjectList;
    std::vector<Camera> cameraList;
    std::vector<ILightSource*> lightSourceList;
    QVector3D backgroundColor;
public:
    Scene();
    Scene(QVector3D backgroundColor);
    ~Scene();
    void render(float time, Camera* camera);
    void addSceneObject(SceneObject *sceneObject);
    Camera& addCamera();
    void addLightSource();
    Camera& getCamera(int cameraNumber);
    void setBackgroundColor(QVector3D color);

    SceneObject &getSceneObject(int id);
    QString name;
};

#endif // SCENE_H
