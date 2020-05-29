#include "Tetraeder.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

Tetraeder::Tetraeder(unsigned char resolution) :
    Geometry(resolution)
{

}

void Tetraeder::generate() {
    float vertices[] = {
         0.0f, sqrt(6.0f)*0.25f, 0.0f,
         0.0f, -1.0f / sqrt(24.0f), -sqrt(3.0f)/3.0f,
        -0.5f, -1.0f / sqrt(24.0f), 0.5f / sqrt(3.0f),
         0.5f, -1.0f / sqrt(24.0f), 0.5f / sqrt(3.0f)
    };

    unsigned int elements[] = {
        0, 1, 3,
        0, 3, 2,
        0, 2, 1,
        1, 2, 3
    };

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
}

void Tetraeder::render() {
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
}
