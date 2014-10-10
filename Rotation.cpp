#include "Rotation.h"

Rotation::Rotation(void)
{
	angle = 0;
	center = Point();
	axis = Point();
	object = NULL;
}

Rotation::Rotation(double newangle, Point & newcenter, Point & newaxis, TransformableObject * newmesh){
	angle = newangle;
	center = newcenter;
	axis = newaxis;
	object = newmesh;
}

Rotation::~Rotation(void)
{
	angle = 0;
	center.~Point();
	axis.~Point();
}


void Rotation::transform(void)
{
	if(object!=NULL){
		glTranslated(-center.getX(),-center.getY(),-center.getZ());
		(*object).setAngle((*object).getAngle()+angle);
		glRotated((*object).getAngle()+angle, axis.getX(), axis.getY(), axis.getZ());
		glTranslated(center.getX(),center.getY(),center.getZ());
	}
}
