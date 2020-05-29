#include "Material.h"

#include <QtMath>

Material::Material(QVector3D albedo, float metallic, float roughness, float ao) :
        albedoTexture(0) {
    setAlbedo(albedo);
    setMetallic(metallic);
    setRouhgness(roughness);
    setAo(ao);
}

Material::Material(unsigned int albedoTexture, float metallic, float roughness, float ao) :
        albedoTexture(albedoTexture) {
    setAlbedo(QVector3D(0.0f, 0.0f, 0.0f));
    setMetallic(metallic);
    setRouhgness(roughness);
    setAo(ao);
}

void Material::setAlbedo(const QVector3D& albedo) {
    //this->albedo = qBound(QVector3D(0.0f, 0.0f, 0.0f), albedo, QVector3D(1.0f, 1.0f, 1.0f));
}

void Material::setAlbedo(const unsigned int albedoTexture) {
    //this->albedoTexture = albedoTexture;
}

void Material::setMetallic(const float &metallic) {
    //this->metallic = qBound(0.0f, metallic, 1.0f);
}

void Material::setRouhgness(const float &roughness) {
    //this->roughness = qBound(0.05f, roughness, 1.0f);
}

void Material::setAo(const float &ao) {
    //this->ao = qBound(0.0f, ao, 1.0f);
}

Material Material::standard() {
    return Material(QVector3D(1.0f, 1.0f, 1.0f), 0.5f, 0.5f, 1.0f);
}
