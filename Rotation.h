#pragma once
#ifndef ROTATION_H
#define ROTATION_H

#include "Transformation.h"
#include "Point.h"

class Rotation:public Transformation
{
public:
	Rotation(void);
	Rotation(double, Point &, Point &, TransformableObject *);
	~Rotation(void);

	void transform(void);

	TransformableObject * getObject(){return object;};
private:
	double angle;
	Point axis;
	Point center;
};
#endif
