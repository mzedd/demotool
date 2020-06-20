#include "Scene.h"

#include "src/modelling/Plane.h"

#include <QOpenGLFunctions>

Scene::Scene() :
    Scene(QVector3D(0.0f, 0.0f, 0.0f)) {
}

Scene::Scene(QVector3D backgroundColor) :
        backgroundColor(backgroundColor) {
    cameraList.push_back(Camera());
    activeCamera = &cameraList[0];
}

Scene::~Scene() {
    for(std::vector<ILightSource*>::iterator it = lightSourceList.begin(); it != lightSourceList.end(); it++) {
        delete *it;
    }
    for(std::vector<SceneObject*>::iterator it = sceneObjectList.begin(); it != sceneObjectList.end(); it++) {
        delete *it;
    }
}

void Scene::render() {

    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();

    // clear background
    f->glClearColor(backgroundColor.x(), backgroundColor.y(), backgroundColor.z(), 1.0f);
    f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

    // setup projection matrix
    //Engine::instance().updateShaderProjectionMatrices();

    int location = 0;

    for(std::vector<SceneObject*>::iterator it = sceneObjectList.begin(); it != sceneObjectList.end(); it++) {
        // pass light to scene objects shader
        location = (*it)->shaderProgram->uniformLocation("lightCount");
        (*it)->shaderProgram->setUniformValue(location, static_cast<int>(lightSourceList.size()));

        for(std::vector<ILightSource*>::iterator lit = lightSourceList.begin(); lit != lightSourceList.end(); lit++) { // TODO: to light passing only per shader
            location = (*it)->shaderProgram->uniformLocation("lightSource[0].type");
            (*it)->shaderProgram->setUniformValue(location, 0);
            location = (*it)->shaderProgram->uniformLocation("lightSource[0].intensity");
            (*it)->shaderProgram->setUniformValue(location, (*lit)->getIntensity());
            location = (*it)->shaderProgram->uniformLocation("lightSource[0].position");
            (*it)->shaderProgram->setUniformValue(location, (*lit)->getPosition());
            //location = (*it)->shaderProgram.uniformLocation("lightSource[0].direction");
            //(*it)->shaderProgram.setUniformValue(location, (*lit)->getDirection());
        }

        location = (*it)->shaderProgram->uniformLocation("view");
        (*it)->shaderProgram->setUniformValue(location, activeCamera->getViewMatrix());
        location = (*it)->shaderProgram->uniformLocation("camPos");
        (*it)->shaderProgram->setUniformValue(location, activeCamera->position);

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
