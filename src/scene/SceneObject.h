#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include <QTransform>
#include <QOpenGLShaderProgram>

#include "../modelling/Geometry.h"
#include "../Material.h"

class SceneObject
{
private:
    Material material;
public:
    QTransform transform;
    Geometry& geometry;
    QOpenGLShaderProgram& shaderProgram;
    SceneObject(Geometry& geometry, QOpenGLShaderProgram& shader);
    void render();
    Material& getMaterial();
    void setMaterial(const Material& material);
};

#endif // SCENEOBJECT_H
