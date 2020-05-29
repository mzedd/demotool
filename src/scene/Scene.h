#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "SceneObject.h"
#include "Camera.h"
#include "light/ILightSource.h"

class Scene
{
private:
    std::vector<SceneObject> sceneObjectList;
    std::vector<Camera> cameraList;
    std::vector<ILightSource*> lightSourceList;
    Camera* activeCamera;
    glm::vec3 backgroundColor;
public:
    Scene();
    Scene(glm::vec3 backgroundColor);
    ~Scene();
    void render();
    void addSceneObject(SceneObject& sceneObject);
    void addCamera(Camera& camera);
    void addLightSource(ILightSource* lightSource);
    Camera& getCamera(int cameraNumber);
    void setEditorCamera();
    void setBackgroundColor(glm::vec3 color);
};

#endif // SCENE_H
