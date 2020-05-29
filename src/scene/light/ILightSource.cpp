#include "ILightSource.h"

ILightSource::ILightSource() :
    intensity(glm::vec3(1.0f))
{

}

ILightSource::ILightSource(glm::vec3 intensity) :
    intensity(intensity) {

}

glm::vec3& ILightSource::getIntensity() {
    return intensity;
}

void ILightSource::setIntensity(glm::vec3 intensity) {
    this->intensity = intensity;
}
