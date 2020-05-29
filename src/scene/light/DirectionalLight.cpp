#include "DirectionalLight.h"

DirectionalLight::DirectionalLight()
{

}

DirectionalLight::DirectionalLight(glm::vec3 intensity, glm::vec3 direction) :
    ILightSource(intensity) {
    setDirection(direction);
}

glm::vec3& DirectionalLight::getDirection() {
    return direction;
}

void DirectionalLight::setDirection(glm::vec3 direction) {
    this->direction = glm::normalize(direction);
}

void DirectionalLight::sendToShader(ShaderProgram &shader, int index) {
    shader.setInt("lightSource.type", 1);
    shader.setUniform("lightSource.intensity", intensity);
    shader.setUniform("lightSource.position", glm::vec3(0.0));
    shader.setUniform("lightSource.direction", direction);
}

