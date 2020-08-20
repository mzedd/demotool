#include "Transform.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

Transform::Transform() :
    position(glm::vec3(0.0f)),
    rotation(glm::quat()),
    scale(glm::vec3(1.0f))
{

}

glm::mat4 Transform::toMat4() {
    glm::mat4 result = glm::mat4(1.0f);

    result = glm::toMat4(rotation);
    result = glm::translate(result, position);
    result = glm::scale(result, scale);

    return result;
}

Transform Transform::unit() {
    return Transform();
}
