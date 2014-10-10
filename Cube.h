#pragma once
#ifndef CUBE_H
#define CUBE_H

#include "mesh.h"
class Cube : public Mesh
{
public:
	Cube(void);
	~Cube(void);
	Cube(const Cube & c);
};
#endif

