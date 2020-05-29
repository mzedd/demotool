#include "Scene.h"
#include "../Engine.h"

Scene::Scene() :
    Scene(glm::vec3(0.0f)) {
}

Scene::Scene(glm::vec3 backgroundColor) :
        backgroundColor(backgroundColor) {
    cameraList.push_back(Camera());
    activeCamera = &cameraList[0];
}

Scene::~Scene() {
    for(std::vector<ILightSource*>::iterator it = lightSourceList.begin(); it != lightSourceList.end(); it++) {
        delete *it;
    }
}

void Scene::render() {
    // clear background
    glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

    // setup projection matrix
    Engine::instance().updateShaderProjectionMatrices();

    for(std::vector<SceneObject>::iterator it = sceneObjectList.begin(); it != sceneObjectList.end(); it++) {
        // pass light to scene objects shader
        it->shaderProgram.setInt("lightCount", static_cast<int>(lightSourceList.size()));
        for(std::vector<ILightSource*>::iterator lit = lightSourceList.begin(); lit != lightSourceList.end(); lit++) { // TODO: to light passing only per shader
            (*lit)->sendToShader(it->shaderProgram, lit-lightSourceList.begin());
        }
        it->shaderProgram.setMat4("view", activeCamera->getViewMatrix());
        it->shaderProgram.setUniform("camPos", activeCamera->position);
        it->render();
    }
}

void Scene::addSceneObject(SceneObject &sceneObject) {
    sceneObjectList.push_back(sceneObject);
}

void Scene::addCamera(Camera &camera) {
    cameraList.push_back(camera);
}

void Scene::addLightSource(ILightSource* lightSource) {
    lightSourceList.push_back(lightSource);
}

Camera& Scene::getCamera(int cameraNumber) {
    return cameraList[cameraNumber];
}

void Scene::setEditorCamera() {
    activeCamera = &Engine::instance().getCamera();
}

void Scene::setBackgroundColor(const glm::vec3 color) {
    backgroundColor = color;
}
