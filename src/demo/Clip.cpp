#include "Clip.h"

#include <iostream>

Clip::Clip()
    : scene(nullptr),
      duration(10.0f),
      name("default") {
}

void Clip::attachScene(Scene *scene) {
    this->scene = scene;
}

void Clip::setDuration(const float duration) {
    this->duration = duration;
}

float Clip::getDuration() {
    return duration;
}

void Clip::render(float time) const
{
    scene->renderAt(time);
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

void Clip::setName(const QString name) {
    this->name = name;
}
