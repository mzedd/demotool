#include "Camera.h"

#include <QtMath>

Camera::Camera() :
    position(0.0f, 0.0f, 0.0f),
    front(QVector3D(0.0f, 0.0f, -1.0f)),
    up(QVector3D(0.0f, 1.0f, 0.0f)),
	speed(1.0f),
	fov(45.0f),
	yaw(0.0f),
	pitch(0.0f),
	lastX(0.0f),
	lastY(0.0f),
	sensitivity(0.1f),
    firstMouse(true) {
}

Camera::Camera(QVector3D position, QVector3D front, QVector3D up, float speed) :
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
    firstMouse(true) {
}

QVector3D Camera::getRight() {
    QVector3D result = QVector3D::crossProduct(front, up);
    result.normalize();
    return result;
}

QVector3D Camera::getUp() {
    return up;
}

QMatrix4x4 Camera::getViewMatrix() {
    QMatrix4x4 result;
    result.lookAt(position, position + front, up);
    return result;
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

    front.setX(cos(qDegreesToRadians(yaw)) * cos(qDegreesToRadians(pitch)));
    front.setY(-sin(qDegreesToRadians(pitch)));
    front.setZ(sin(qDegreesToRadians(yaw)) * cos(qDegreesToRadians(pitch)));
    front.normalize();
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

QMatrix4x4 Camera::getProjectionMatrix(int width, int height) {
    QMatrix4x4 result;
    result.perspective(qDegreesToRadians(fov), width/(double)height, 0.1, 100.0f);
    return result;
}
