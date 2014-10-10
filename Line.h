#pragma once
#ifndef LINE_H
#define LINE_H

#include "TransformableObject.h"
#include "Point.h"

class Line :
	public TransformableObject
{
public:
	Line(void);
	Line(const Point & newp1, const Point & newp2);
	Line(const Line & l);
	~Line(void);

	Line & operator=(const Line & l);
	
	Point & getP1(void){return p1;}
	Point & getP2(void){return p2;}
	void setPoints(const Point & newp1, const Point & newp2){p1 = newp1; p2 = newp2;}
private:
	Point p1;
	Point p2;
public:
	void draw(void);
};

#endif