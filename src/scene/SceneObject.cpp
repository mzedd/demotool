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

        int location = shaderProgram->uniformLocation("model");
        shaderProgram->setUniformValue(location, QMatrix4x4(transform));

        location = shaderProgram->uniformLocation("material.albedo");
        shaderProgram->setUniformValue(location, material.albedo);

        location = shaderProgram->uniformLocation("material.metallic");
        shaderProgram->setUniformValue(location, material.metallic);

        location = shaderProgram->uniformLocation("material.roughness");
        shaderProgram->setUniformValue(location, material.roughness);

        location = shaderProgram->uniformLocation("material.albedoTexture");
        shaderProgram->setUniformValue(location, false);
    } else {
        qDebug() << "No Shader attached";
    }

    geometry->render();
}

Material& SceneObject::getMaterial() {
    return material;
}

void SceneObject::setMaterial(const Material &material) {
    this->material = material;
}
