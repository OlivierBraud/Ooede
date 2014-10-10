#pragma once
#ifndef TRANSLATION_H
#define TRANSLATION_H

#include "Transformation.h"

class Translation:public Transformation
{
public:
	Translation(void);
	Translation(double, double, double, TransformableObject *);
	~Translation(void);

	void transform(void);

	TransformableObject * getObject(){return object;};
private:
	double x;
	double y;
	double z;
};
#endif
