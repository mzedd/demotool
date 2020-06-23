#include "Scene.h"

#include "src/modelling/Plane.h"

#include <QOpenGLFunctions>

Scene::Scene() :
    Scene(QVector3D(0.0f, 0.0f, 0.0f)) {
}

Scene::Scene(QVector3D backgroundColor) :
        backgroundColor(backgroundColor) {
    cameraList.push_back(Camera());
}

Scene::~Scene() {
    for(std::vector<ILightSource*>::iterator it = lightSourceList.begin(); it != lightSourceList.end(); it++) {
        delete *it;
    }
    for(std::vector<SceneObject*>::iterator it = sceneObjectList.begin(); it != sceneObjectList.end(); it++) {
        delete *it;
    }
}

void Scene::render(float time, Camera* camera) {

    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();

    // clear background
    f->glClearColor(backgroundColor.x(), backgroundColor.y(), backgroundColor.z(), 1.0f);
    f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

    for(std::vector<SceneObject*>::iterator it = sceneObjectList.begin(); it != sceneObjectList.end(); it++) {
        // pass light to scene objects shader
        (*it)->shaderProgram->setUniformValue("lightCount", static_cast<int>(lightSourceList.size()));

        for(std::vector<ILightSource*>::iterator lit = lightSourceList.begin(); lit != lightSourceList.end(); lit++) { // TODO: to light passing only per shader
            (*it)->shaderProgram->setUniformValue("lightSource[0].type", 0);
            (*it)->shaderProgram->setUniformValue("lightSource[0].intensity", (*lit)->getIntensity());
            (*it)->shaderProgram->setUniformValue("lightSource[0].direction", (*lit)->getPosition());
            //location = (*it)->shaderProgram.uniformLocation("lightSource[0].direction");
            //(*it)->shaderProgram.setUniformValue(location, (*lit)->getDirection());
        }

        (*it)->shaderProgram->setUniformValue("projection", camera->getProjectionMatrix());
        (*it)->shaderProgram->setUniformValue("view", camera->getViewMatrix());
        (*it)->shaderProgram->setUniformValue("camPos", camera->position);

        (*it)->render();
    }
}

void Scene::addSceneObject(SceneObject *sceneObject) {
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
    //activeCamera = &Engine::instance().getCamera();
}

void Scene::setBackgroundColor(QVector3D color) {
    backgroundColor = color;
}

SceneObject &Scene::getSceneObject(int id)
{
    return *sceneObjectList[id];
}
