#include "Geometry.h"

Geometry::Geometry(unsigned char resolution) :
	vao(0),
    vbo(QOpenGLBuffer::Type::VertexBuffer),
    ebo(QOpenGLBuffer::Type::IndexBuffer),
    resolution(resolution) {
}

Geometry::~Geometry() {
    vao.destroy();
    ebo.destroy();
    vbo.destroy();
}

void Geometry::setResolution(unsigned char resolution) {
	this->resolution = resolution;
}
