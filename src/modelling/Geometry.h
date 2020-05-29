#ifndef GEOMETRY_H
#define GEOMETRY_H

class Geometry {
protected:
	unsigned int vao, vbo, ebo;
	unsigned char resolution;
public:
    Geometry(unsigned char resolution);
    virtual ~Geometry();
	void setResolution(unsigned char resolution);
	virtual void generate() = 0;
	virtual void render() = 0;
};

#endif /* GEOMETRY_H */
