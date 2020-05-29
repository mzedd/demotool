#include "Geometry.h"

#include <glad/glad.h>

Geometry::Geometry(unsigned char resolution) :
	vao(0),
	vbo(0),
	ebo(0),
	resolution(resolution) {
}

Geometry::~Geometry() {
    glDeleteBuffers(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
}

void Geometry::setResolution(unsigned char resolution) {
	this->resolution = resolution;
}
