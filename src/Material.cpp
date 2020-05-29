#include "Material.h"

Material::Material(glm::vec3 albedo, float metallic, float roughness, float ao) :
        albedoTexture(0) {
    setAlbedo(albedo);
    setMetallic(metallic);
    setRouhgness(roughness);
    setAo(ao);
}

Material::Material(unsigned int albedoTexture, float metallic, float roughness, float ao) :
        albedoTexture(albedoTexture) {
    setAlbedo(glm::vec3(0.0f));
    setMetallic(metallic);
    setRouhgness(roughness);
    setAo(ao);
}

void Material::setAlbedo(const glm::vec3& albedo) {
    this->albedo = glm::clamp(albedo, glm::vec3(0.0f), glm::vec3(1.0f));
}

void Material::setAlbedo(const unsigned int albedoTexture) {
    this->albedoTexture = albedoTexture;
}

void Material::setMetallic(const float &metallic) {
    this->metallic = glm::clamp(metallic, 0.0f, 1.0f);
}

void Material::setRouhgness(const float &roughness) {
    this->roughness = glm::clamp(roughness, 0.05f, 1.0f);
}

void Material::setAo(const float &ao) {
    this->ao = glm::clamp(ao, 0.0f, 1.0f);
}

Material Material::standard() {
    return Material(glm::vec3(1.0f), 0.5f, 0.5f, 1.0f);
}
