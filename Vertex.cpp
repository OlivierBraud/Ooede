#include "Vertex.h"


Vertex::Vertex(void)
{
	centerPosition = Point(0,0,0);
}

Vertex::Vertex(const Vertex & v)
{
	if(&v!=this){
		centerPosition = v.centerPosition;
	}
}

Vertex::Vertex(const Point & p)
{
	centerPosition = p;
}

void Vertex::draw(){
	glBegin(GL_POINTS);
	glVertex3d(centerPosition.getX(),centerPosition.getY(),centerPosition.getZ());
	glEnd();
}

Vertex & Vertex::operator=(const Vertex & v)
{
	if(&v!=this){
		centerPosition = v.centerPosition;
	}
	return * this;
}
