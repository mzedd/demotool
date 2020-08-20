#include "ILightSource.h"

ILightSource::ILightSource() :
    intensity(QVector3D(1.0f, 1.0f, 1.0f))
{

}

ILightSource::ILightSource(QVector3D intensity) :
    intensity(intensity) {

}

QVector3D& ILightSource::getIntensity() {
    return intensity;
}

void ILightSource::setIntensity(QVector3D intensity) {
    this->intensity = intensity;
}
