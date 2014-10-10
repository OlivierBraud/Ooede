#pragma once
#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include "TransformableObject.h"
#include "Mesh.h"
#include "Camera.h"
#include "Light.h"

class Transformation
{
public:
	virtual void transform() = 0;
	virtual TransformableObject * getObject() = 0;
protected:
	TransformableObject * object;
};
#endif