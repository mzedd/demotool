#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include <glm/glm.hpp>
#include "ILightSource.h"

class PointLight : public ILightSource
{
private:
    glm::vec3 position;
public:
    PointLight();
    PointLight(glm::vec3 intensity, glm::vec3 position);
    void sendToShader(ShaderProgram &shader, int index);
};

#endif // POINTLIGHT_H
