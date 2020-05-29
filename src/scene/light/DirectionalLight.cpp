#include "DirectionalLight.h"

DirectionalLight::DirectionalLight()
{

}

DirectionalLight::DirectionalLight(QVector3D intensity, QVector3D direction) :
    ILightSource(intensity) {
    setDirection(direction);
}

QVector3D& DirectionalLight::getDirection() {
    return direction;
}

void DirectionalLight::setDirection(QVector3D direction) {
    this->direction = direction;
    this->direction.normalize();
}

void DirectionalLight::sendToShader(QOpenGLShaderProgram &shader, int index) {
    /*shader.setInt("lightSource.type", 1);
    shader.setUniform("lightSource.intensity", intensity);
    shader.setUniform("lightSource.position", QVector3D(0.0));
    shader.setUniform("lightSource.direction", direction);*/
}

