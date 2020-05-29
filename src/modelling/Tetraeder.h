#ifndef TETRAEDER_H
#define TETRAEDER_H

#include "Geometry.h"

class Tetraeder : public Geometry
{
public:
    Tetraeder(unsigned char resolution);
    void generate();
    void render();
};

#endif // TETRAEDER_H
