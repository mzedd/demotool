#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera() :
	position(glm::vec3(0.0f)),
	front(glm::vec3(0.0f, 0.0f, -1.0f)),
	up(glm::vec3(0.0f, 1.0f, 0.0f)),
	speed(1.0f),
	fov(45.0f),
	yaw(0.0f),
	pitch(0.0f),
	lastX(0.0f),
	lastY(0.0f),
	sensitivity(0.1f),
	firstMouse(false) {
}

Camera::Camera(glm::vec3 position, glm::vec3 front, glm::vec3 up, float speed) :
	position(position),
	front(front),
	up(up),
	speed(speed),
	fov(45.0f),
	yaw(-90.0f),
	pitch(0.0f),
	lastX(400),
	lastY(300),
	sensitivity(0.1f),
	firstMouse(false) {
}

glm::vec3 Camera::getRight() {
	return glm::normalize(glm::cross(front, up));
}

glm::vec3 Camera::getUp() {
    return up;
}

glm::mat4 Camera::getViewMatrix() {
	return glm::lookAt(position, position + front, up);
}

void Camera::updateFront(float xpos, float ypos) {
	if (firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = ypos - lastY;
	lastX = xpos;
	lastY = ypos;

	yaw += xoffset * sensitivity;
	pitch += yoffset * sensitivity;

	if (pitch > 89.0f) {
		pitch = 89.0f;
	}
	else if (pitch < -89.0f) {
		pitch = -89.0f;
	}

	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = -sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);
}

void Camera::addScrollOffset(float offset) {
	fov -= offset;

	if (fov > 45.0f) {
		fov = 45.0f;
	}
	else if (fov < 1.0f) {
		fov = 1.0f;
	}
}

glm::mat4 Camera::getProjectionMatrix(int width, int height) {
	return glm::perspective(glm::radians(fov), (float)width / (float)height, 0.1f, 100.0f);
}
