#include "Translation.h"


Translation::Translation(void)
{
	x=0, y=0, z=0;
	object = NULL;
}

Translation::Translation(double newx, double newy, double newz, TransformableObject * newmesh)
{
	x=newx, y=newy, z=newz;
	object = newmesh;
}

Translation::~Translation(void)
{
	x=0, y=0, z=0;
}


void Translation::transform(void)
{
	if(object!=NULL){
		(*object).getCenterPosition().setCoordinates(
			(*object).getCenterPosition().getX()+x,
			(*object).getCenterPosition().getY()+y,
			(*object).getCenterPosition().getZ()+z);
		glTranslated((*object).getCenterPosition().getX(),
			(*object).getCenterPosition().getY(),
			(*object).getCenterPosition().getZ());
	}
}
