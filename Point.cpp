#include "Point.h"


Point::Point(void)
{
	x = 0;
	y = 0;
	z = 0;
	tab = new float[3];
}

Point::Point(const double newx, const double newy, const double newz)
{
	x = newx;
	y = newy;
	z = newz;
	tab = new float[3];
}

Point::Point(const Point & point)
{
	x = point.x;
	y = point.y;
	z = point.z;
	tab = new float[3];
}

Point & Point::operator=(const Point & point){
	if(this!=&point){
		x = point.x;
		y = point.y;
		z = point.z;
		tab = new float[3];
	}
	return * this;
}

float * Point::getFloatArray3(void){
	tab = new float[3];
	tab[0] = (float)x, tab[1] = (float)y, tab[2] = (float)z;
	return tab;
}

float * Point::getFloatArray4(float w){
	tab = new float[4];
	tab[0] = (float)x, tab[1] = (float)y, tab[2] = (float)z, tab[3] = w;
	return tab;
}

Point Point::operator-(const Point & p){
	return Point(x-p.x,y-p.y,z-p.z);
}

Point Point::operator+(const Point & p){
	return Point(x+p.x,y+p.y,z+p.z);
}

Point Point::operator*(const Point & p){
	return Point(x*p.x,y*p.y,z*p.z);
}

Point::~Point(void)
{
	delete tab;
}
