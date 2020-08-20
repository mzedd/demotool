#include "SceneObject.h"

SceneObject::SceneObject(Geometry *geometry, QOpenGLShaderProgram *shader) :
    material(Material::standard()),
    transform(),
    geometry(geometry),
    shaderProgram(shader)
{
    geometry->generate();
}

SceneObject::~SceneObject()
{
    /*if(geometry) {
        delete geometry;
    }*/
}

void SceneObject::render() {

    if(shaderProgram) {
        shaderProgram->bind();
        shaderProgram->setUniformValue("model", QMatrix4x4(transform));
        shaderProgram->setUniformValue("material.albedo", material.albedo);
        shaderProgram->setUniformValue("material.metallic", material.metallic);
        shaderProgram->setUniformValue("material.roughness", material.roughness);
        shaderProgram->setUniformValue("material.albedoTexture", false);

    } else {
        qDebug() << "No Shader attached";
    }

    geometry->render();
    qDebug() << "scene object rendernd";
}

Material& SceneObject::getMaterial() {
    return material;
}

void SceneObject::setMaterial(const Material &material) {
    this->material = material;
}
