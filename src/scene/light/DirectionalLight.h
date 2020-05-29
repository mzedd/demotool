#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H

#include <glm/glm.hpp>
#include "ILightSource.h"

class DirectionalLight : public ILightSource
{
private:
    glm::vec3 direction;
public:
    DirectionalLight();
    DirectionalLight(glm::vec3 intensity, glm::vec3 direction);
    glm::vec3& getDirection();
    void setDirection(glm::vec3 direction);
    void sendToShader(ShaderProgram &shader, int index);
};

#endif // DIRECTIONALLIGHT_H
