#include "PointLight.h"

#include <string>

PointLight::PointLight()
{

}

PointLight::PointLight(glm::vec3 intensity, glm::vec3 position) :
    ILightSource(intensity),
    position(position) {
    this->intensity = intensity;
}

void PointLight::sendToShader(ShaderProgram &shader, int index) {
    std::string name("lightSource[");
    name = name + std::to_string(index) + "].";
    shader.setInt(name + "type", 0);
    shader.setUniform(name + "intensity", intensity);
    shader.setUniform(name + "position", position);
    shader.setUniform(name + "direction", glm::vec3(0.0));
}
