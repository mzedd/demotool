#ifndef PLANE_H
#define PLANE_H

#include "Geometry.h"

class Plane : public Geometry
{
private:
    float width;
    float height;
    int indexCount;
public:
    Plane();
    Plane(unsigned char resolution, float width, float height);

    void generate() override;
    void render() override;
};

#endif // PLANE_H
