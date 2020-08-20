#ifndef CAMERA_H
#define CAMERA_H

#include <QVector3D>
#include <QMatrix4x4>

class Camera {
private:
	float yaw;
	float pitch;

    QMatrix4x4 projection;

public:
    QVector3D position;
    QVector3D front;
    QVector3D up;
	float speed;
	float fov;
	float lastX, lastY, sensitivity;
	bool firstMouse;
	
	Camera();
    Camera(QVector3D position, QVector3D front, QVector3D up, float speed);
    QVector3D getRight();
    QVector3D getUp();
    QMatrix4x4 getViewMatrix();
    const QMatrix4x4 &getProjectionMatrix();
	void updateFront(float xpos, float ypos);
    void addScrollOffset(float offset);
    void updateProjectionMatrix(const int width, const int height);
};

#endif /* CAMERA_H */
