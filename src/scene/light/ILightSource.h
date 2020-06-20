#ifndef ILIGHTSOURCE_H
#define ILIGHTSOURCE_H

#include <QVector3D>
#include <QOpenGLShaderProgram>

class ILightSource
{
protected:
    QVector3D intensity;
public:
    ILightSource();
    ILightSource(QVector3D intesity);
    virtual ~ILightSource() = default;
    QVector3D& getIntensity();
    void setIntensity(QVector3D intensity);
    virtual QVector3D getPosition() = 0;
    virtual void sendToShader(QOpenGLShaderProgram& shader,int index) = 0;
};

#endif // ILIGHTSOURCE_H
