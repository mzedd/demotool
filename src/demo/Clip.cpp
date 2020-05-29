#include "Clip.h"

#include <iostream>

Clip::Clip() :
    scene(nullptr),
    camera(nullptr) {

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
