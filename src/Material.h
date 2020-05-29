#ifndef MATERIAL_H
#define MATERIAL_H

#include <QVector3D>

class Material {
public:
    QVector3D albedo;
    unsigned int albedoTexture;
	float metallic;
	float roughness;
	float ao;

    Material(QVector3D albedo, float metallic, float roughness, float ao);
    Material(unsigned int albedoTexture, float metallic, float roughness, float ao);
    void setAlbedo(const QVector3D& albedo);
    void setAlbedo(const unsigned int albedoTexture);
    void setMetallic(const float& metallic);
    void setRouhgness(const float& roughness);
    void setAo(const float& ao);

    static Material standard();
};

#endif /* MATERIAL_H */
