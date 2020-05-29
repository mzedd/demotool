#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include <QVector3D>

#include "ILightSource.h"

class PointLight : public ILightSource
{
private:
    QVector3D position;
public:
    PointLight();
    PointLight(QVector3D intensity, QVector3D position);
    void sendToShader(QOpenGLShaderProgram &shader, int index);
};

#endif // POINTLIGHT_H
