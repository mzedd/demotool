#ifndef SPHERE_H
#define SPHERE_H

#include "Geometry.h"

class Sphere : public Geometry {
private:
	float radius;
	unsigned int indexCount;
public:
	Sphere(unsigned char resolution, float radius);
	float getRadius();
	void setRadius(float radius);
	void generate();
	void render();
};

#endif /* SPHERE_H */
