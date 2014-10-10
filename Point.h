#pragma once
#ifndef POINT_H
#define POINT_H

#include <Windows.h>
#include <gl/GL.h>

class Point
{
public:
	Point(void);
	Point(const double, const double, const double);
	Point(const Point &);
	~Point(void);

	Point & operator=(const Point &);
	Point operator-(const Point &);
	Point operator+(const Point &);
	Point operator*(const Point &);

	float * getFloatArray4(float);
	float * getFloatArray3();
	double getX(){return x;};
	double getY(){return y;};
	double getZ(){return z;};
	void setCoordinates(double newx, double newy, double newz){x=newx; y=newy; z=newz;}

private:
	double x;
	double y;
	double z;
	float * tab;
public:
	static const char AXIS_X = 'x';
	static const char AXIS_Y = 'y';
	static const char AXIS_Z = 'z';
};
#endif
