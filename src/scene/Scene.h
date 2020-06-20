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
    Camera* activeCamera;
    QVector3D backgroundColor;
public:
    Scene();
    Scene(QVector3D backgroundColor);
    ~Scene();
    void render();
    void addSceneObject(SceneObject *sceneObject);
    void addCamera(Camera& camera);
    void addLightSource(ILightSource* lightSource);
    Camera& getCamera(int cameraNumber);
    void setEditorCamera();
    void setBackgroundColor(QVector3D color);

    SceneObject &getSceneObject(int id);


    QString name;

};

#endif // SCENE_H
