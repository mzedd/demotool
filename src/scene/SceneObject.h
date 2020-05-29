#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "Transform.h"
#include "../modelling/Geometry.h"
#include "../Material.h"
#include "../ShaderProgram.h"

class SceneObject
{
private:
    Material material;

public:
    Transform transform;
    Geometry& geometry;
    ShaderProgram& shaderProgram;
    SceneObject(Geometry& geometry, ShaderProgram& shader);
    void render();
    Material& getMaterial();
    void setMaterial(const Material& material);
};

#endif // SCENEOBJECT_H
