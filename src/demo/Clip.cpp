#include "Clip.h"

#include <iostream>

Clip::Clip()
    : scene(nullptr),
      camera(nullptr),
      duration(10.0f),
      name("default") {
}

void Clip::attachScene(Scene *scene) {
    this->scene = scene;
}

void Clip::attachCamera(int cameraNumber) {
    if(scene) {
        camera = &(scene->getCamera(cameraNumber));
    } else {
        std::cout << "Attach a Scene first" << std::endl;
    }
}

void Clip::setDuration(const float duration) {
    this->duration = duration;
}

float Clip::getDuration() {
    return duration;
}

void Clip::render(float time) const
{
    if(camera) {
        scene->render(time, camera);
        qDebug() << "scene renderd";
    }
}

QString Clip::getName() const {
    return name;
}

Scene* Clip::getScene() const
{
    if(scene) {
        return scene;
    }
    return nullptr;
}

Camera &Clip::getCamera()
{
    return *camera;
}

void Clip::setName(const QString name) {
    this->name = name;
}
