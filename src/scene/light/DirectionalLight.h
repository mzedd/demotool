#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H

#include <QVector3D>

#include "ILightSource.h"

class DirectionalLight : public ILightSource
{
private:
    QVector3D direction;
public:
    DirectionalLight();
    DirectionalLight(QVector3D intensity, QVector3D direction);
    QVector3D& getDirection();
    void setDirection(QVector3D direction);
    void sendToShader(QOpenGLShaderProgram &shader, int index);
};

#endif // DIRECTIONALLIGHT_H
