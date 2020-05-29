#ifndef CYLINDER_H
#define CYLINDER_H

#include "Geometry.h"

class Cylinder : public Geometry {
private:
	float radius;
	float height;
    unsigned int indexCount;
public:
	Cylinder(unsigned char resolution, float radius, float height);
	void generate();
	void render();
};

#endif /* CYLINDER_H */
