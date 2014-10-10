#pragma once
#ifndef FACE_H
#define FACE_H

#include <Windows.h>
#include <exception>
#include <GL/GL.h>
#include <vector>
#include <math.h>

#include "Point.h"

class Face
{
public:
	Face(void);
	Face(Point & p1, Point & p2, Point & p3);
	Face(Point & p1, Point & p2, Point & p3, Point & p4);
	Face(const Face & f);
	~Face(void);

	Point & operator[](unsigned int i);
	Face & operator=(const Face &);

	void addMapping(Point &);
	void rescale(const Point & newsize);
	void rotate(double, Point &);
	void draw(void);

	unsigned int getPointsCount(void) const;
	Point getGravityCenter(void);

private:
	std::vector<Point> points;
	std::vector<Point> textureMapping;
};
#endif
