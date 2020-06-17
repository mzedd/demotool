#include "Clip.h"

#include <iostream>

Clip::Clip()
    : Clip("clip")
{
    duration = 10.0f;
}

Clip::Clip(QString name)
    : scene(nullptr),
      camera(nullptr),
      duration(0.0f),
      name(name)
{
}

void Clip::attachScene(Scene &scene) {
    this->scene = &scene;
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

QString Clip::getName() const {
    return name;
}

Scene &Clip::getScene() const
{
    if(scene) {
        return *scene;
    }
}

void Clip::setName(const QString name) {
    this->name = name;
}
