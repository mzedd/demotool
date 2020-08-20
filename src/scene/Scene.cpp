#include "Scene.h"

#include "src/modelling/Plane.h"

#include <QOpenGLFunctions>

#include "scene/light/PointLight.h"

Scene::Scene() :
    Scene(QVector3D(0.0f, 0.0f, 0.0f)) {
}

Scene::Scene(QVector3D backgroundColor) :
        backgroundColor(backgroundColor) {
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
        (*it)->shaderProgram->bind();
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
        (*it)->shaderProgram->setUniformValue("iProgress", time*0.1f);

        qDebug() << camera->position;

        (*it)->render();
    }
}

void Scene::addSceneObject(SceneObject *sceneObject) {
    sceneObjectList.push_back(sceneObject);
}

Camera& Scene::addCamera() {
    cameraList.push_back(Camera());
    return cameraList.back();
}

void Scene::addLightSource() {
    lightSourceList.push_back(new PointLight());
}

Camera& Scene::getCamera(int cameraNumber) {

    return cameraList[cameraNumber];
}

void Scene::setBackgroundColor(QVector3D color) {
    backgroundColor = color;
}

SceneObject &Scene::getSceneObject(int id)
{
    return *sceneObjectList[id];
}
