#ifndef ILIGHTSOURCE_H
#define ILIGHTSOURCE_H

#include <glm/glm.hpp>
#include "../../ShaderProgram.h"

class ILightSource
{
protected:
    glm::vec3 intensity;
public:
    ILightSource();
    ILightSource(glm::vec3 intesity);
    virtual ~ILightSource() = default;
    glm::vec3& getIntensity();
    void setIntensity(glm::vec3 intensity);
    virtual void sendToShader(ShaderProgram& shader,int index) = 0;
};

#endif // ILIGHTSOURCE_H
