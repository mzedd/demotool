#include "PointLight.h"

#include <string>

PointLight::PointLight()
{

}

PointLight::PointLight(QVector3D intensity, QVector3D position) :
    ILightSource(intensity),
    position(position) {
    this->intensity = intensity;
}

void PointLight::sendToShader(QOpenGLShaderProgram &shader, int index) {
    std::string name("lightSource[");
    name = name + std::to_string(index) + "].";
    //shader.setInt(name + "type", 0);
    //shader.setUniform(name + "intensity", intensity);
    //shader.setUniform(name + "position", position);
    //shader.setUniform(name + "direction", QVector3D(0.0f, 0.0f, 0.0f));
}
