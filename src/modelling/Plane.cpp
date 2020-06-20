#include "Plane.h"

#include <QVector3D>
#include <QOpenGLFunctions>

Plane::Plane() :
    Geometry(1),
    width(1.0f),
    height(1.0f),
    indexCount(0) {

}

Plane::Plane(unsigned char resolution, float width, float height) :
    Geometry(resolution),
    width(width),
    height(height),
    indexCount(0) {
}

void Plane::generate() {
    vao.create();
    vbo.create();
    ebo.create();

    int verticeCount = (2+resolution)*(2+resolution);
    float* data = new float[8*verticeCount];
    int arrayIndex = 0;

    for(int x = 0; x < resolution+2; x++) {
        for(int y = 0; y < resolution+2; y++) {
            float relativeX = (float)x/(float)(resolution+1);
            float relativeY = (float)y/(float)(resolution+1);
            QVector3D r;
            r.setX((relativeX-0.5f) * width);
            r.setY(0.0f);
            r.setZ((relativeY-0.5f) * height);

            QVector3D normal(0.0f, 1.0f, 0.0f);

            data[arrayIndex] = r.x();
            data[arrayIndex+1] = r.y();
            data[arrayIndex+2] = r.z();
            data[arrayIndex+3] = normal.x();
            data[arrayIndex+4] = normal.y();
            data[arrayIndex+5] = normal.z();
            data[arrayIndex+6] = relativeX;
            data[arrayIndex+7] = relativeY;

            arrayIndex += 8;
        }
    }

    indexCount = (resolution+2)*2*(resolution+1);
    unsigned int *indices = new unsigned int[indexCount];

    for(int i = 0; i < resolution+1; i++) {
        for(int k = 0; k < resolution+2; k++) {
            indices[i*(resolution+2)*2+2*k] = (resolution+2)*i+k;
            indices[i*(resolution+2)*2+2*k+1] = (resolution+2)*i+(resolution+2)+k;
        }
    }

    vao.bind();
    vbo.bind();
    vbo.allocate(data, verticeCount*8*sizeof(float));
    ebo.bind();
    ebo.allocate(indices, indexCount * sizeof(unsigned int));
    /*glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6 * sizeof(float)));
*/
    delete[] data;
    delete[] indices;
}

void Plane::render() {
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();

    vao.bind();
    for(int i = 0; i < resolution+2; i++) {
        f->glDrawElements(GL_TRIANGLE_STRIP, (resolution+2)*2, GL_UNSIGNED_INT, (void*)((resolution+2)*2*i*sizeof(unsigned int)));
    }
}
