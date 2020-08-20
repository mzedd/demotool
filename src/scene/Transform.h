#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class Transform
{
public:
    glm::vec3 position;
    glm::quat rotation;
    glm::vec3 scale;

    Transform();
    glm::mat4 toMat4();


    static Transform unit();
};


#endif // TRANSFORM_H
