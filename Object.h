#pragma once
#ifndef OBJECT_H
#define OBJECT_H

#include <Windows.h>
#include "Point.h"
#include <GL/GL.h>
#include <string>

class Object
{
public:
	virtual void draw(void) = 0;

	virtual std::string & getName(void) = 0;
	virtual void setName(std::string newName) = 0;
	virtual Point & getCenterPosition(void) = 0;
	virtual void setCenterPosition(Point &) = 0;
	virtual double getAngle() = 0;
	virtual void setAngle(double newangle) = 0;
	virtual Point & getScale() = 0;
	virtual void setScale(double x, double y, double z) = 0;
protected:
	Point centerPosition;
	double angle;
	Point scale;
	std::string name;
	

};
#endif
