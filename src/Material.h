#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/glm.hpp>

class Material {
public:
    glm::vec3 albedo;
    unsigned int albedoTexture;
	float metallic;
	float roughness;
	float ao;

    Material(glm::vec3 albedo, float metallic, float roughness, float ao);
    Material(unsigned int albedoTexture, float metallic, float roughness, float ao);
    void setAlbedo(const glm::vec3& albedo);
    void setAlbedo(const unsigned int albedoTexture);
    void setMetallic(const float& metallic);
    void setRouhgness(const float& roughness);
    void setAo(const float& ao);

    static Material standard();
};

#endif /* MATERIAL_H */
