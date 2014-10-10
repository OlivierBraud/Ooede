#include "Line.h"

Line::Line(void)
{
	p1 = Point(1,0,0);
	p2 = Point(0,1,0);
}

Line::Line(const Point & newp1, const Point & newp2)
{
	p1 = newp1;
	p2 = newp2;
}


Line::Line(const Line & l)
{
	if(&l!=this){
		p1 = l.p1;
		p2 = l.p2;
	}
}

Line & Line::operator=(const Line & l)
{
	if(&l!=this){
		p1 = l.p1;
		p2 = l.p2;
	}
	return * this;
}

void Line::draw(void)
{
	glBegin(GL_LINES);
	glVertex3d(p1.getX(),p1.getY(),p1.getZ());
	glVertex3d(p2.getX(), p2.getY(), p2.getZ());
	glEnd();
}
