#include "Cylinder.h"

#include <vector>
#include <iostream>

#include <glad/glad.h>
#include <glm/glm.hpp>

Cylinder::Cylinder(unsigned char resolution, float radius, float height) :
	Geometry(resolution),
	radius(radius),
    height(height),
    indexCount(0) {

}

void Cylinder::generate() {
	glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;

    int verticeCount = 2*(resolution+1)+2*resolution+4;

    float pi = acos(-1.0f);

    // generate vertices and normals for top and bottom faces
    for (int iZ = 0; iZ < 2; iZ++) {
        float z = iZ * height;

        vertices.push_back(glm::vec3(0.0f, z, 0.0f));
        normals.push_back(glm::normalize(glm::vec3(0.0,-1.0f+iZ*2.0f, 0.0f)));

        for (int iPhi = 0; iPhi < resolution+1; iPhi++) {
            float phi = iPhi * (2.0f * pi / (float)resolution ); // TODO: get pi from somewhere else

            glm::vec3 r;
            r.x = radius * cos(phi);
            r.y = z;
            r.z = radius * sin(phi);

            glm::vec3 normal = glm::vec3(0.0,-1.0f+iZ*2.0f, 0.0f);

            vertices.push_back(r);
            normals.push_back(normal);
        }
    }

    // generate vertices and normals for the hull
    for (int iPhi = 0; iPhi < resolution+1; iPhi++) {
        float phi = iPhi * (2.0f * pi / (float)resolution ); // TODO: get pi from somewhere else

        for (int iZ = 0; iZ < 2; iZ++) {
            float z = iZ * height;
			glm::vec3 r;
			r.x = radius * cos(phi);
			r.y = z;
			r.z = radius * sin(phi);

			glm::vec3 normal = glm::normalize(r - glm::vec3(0.0f, z, 0.0f));

			vertices.push_back(r);
            normals.push_back(normal);
		}
    }

    float* data = new float[6*verticeCount];

    for(int i = 0; i < verticeCount; i++) {
        data[6*i] = vertices[i].x;
        data[(6*i)+1] = vertices[i].y;
        data[(6*i)+2] = vertices[i].z;
        data[(6*i)+3] = normals[i].x;
        data[(6*i)+4] = normals[i].y;
        data[(6*i)+5] = normals[i].z;
    }

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, verticeCount*6*sizeof(float), data, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3 * sizeof(float)));

    delete[](data);
}

void Cylinder::render() {
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLE_FAN, 0, resolution+2);
    glDrawArrays(GL_TRIANGLE_FAN, resolution+2, resolution+2);
    glDrawArrays(GL_TRIANGLE_STRIP, 2*(resolution+2), 2*resolution+2);
}
