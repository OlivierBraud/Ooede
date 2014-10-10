#pragma once
#ifndef CYLINDER_H
#define CYLINDER_H
#define _USE_MATH_DEFINES

#include <math.h>
#include "Mesh.h"

class Cylinder :
	public Mesh
{
public:
	Cylinder(void);
	Cylinder(unsigned int segments);
	Cylinder(const Cylinder & c);
	~Cylinder(void);
private:
	unsigned int segments;
	
};
#endif

