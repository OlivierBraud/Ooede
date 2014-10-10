#pragma once
#ifndef UVSPHERE_H
#define UVSPHERE_H
#define _USE_MATH_DEFINES

#include <math.h>
#include "mesh.h"

class UvSphere :
	public Mesh
{
public:
	UvSphere(void);
	UvSphere(const UvSphere & s);
	UvSphere(unsigned int segments, unsigned int rings);
	~UvSphere(void);

	UvSphere & operator=(const UvSphere & s);
	
	unsigned int getSegments(void){return segments;};
	unsigned int getRings(void){return rings;};

private:
	unsigned int segments;
	unsigned int rings;
};
#endif
