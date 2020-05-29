#ifndef CAMERA_H
#define CAMERA_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Camera {
private:
	float yaw;
	float pitch;

public:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	float speed;
	float fov;
	float lastX, lastY, sensitivity;
	bool firstMouse;
	
	Camera();
	Camera(glm::vec3 position, glm::vec3 front, glm::vec3 up, float speed);
    glm::vec3 getRight();
    glm::vec3 getUp();
	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix(int width, int height);
	void updateFront(float xpos, float ypos);
    void addScrollOffset(float offset);
};

#endif /* CAMERA_H */
