#pragma once
#ifndef RESCALING_H
#define RESCALING_H

#include "Transformation.h"

class Rescaling:public Transformation
{
public:
	Rescaling(void);
	Rescaling(double, double, double, TransformableObject *);
	~Rescaling(void);

	void transform(void);

	TransformableObject * getObject(){return object;};
private:
	double scaleX;
	double scaleY;
	double scaleZ;
};
#endif
