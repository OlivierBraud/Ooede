#include "Rescaling.h"


Rescaling::Rescaling(void)
{
	scaleX = 0, scaleY = 0, scaleZ = 0;
	object = NULL;
}

Rescaling::Rescaling(double x, double y, double z, TransformableObject * newMesh)
{
	scaleX = x, scaleY = x, scaleZ = z;
	object = newMesh;
}

Rescaling::~Rescaling(void)
{
	scaleX = 0, scaleY = 0, scaleZ = 0;
}


void Rescaling::transform(void)
{
	if(object!=NULL){
		double newscalex = (*object).getScale().getX() * scaleX;
		double newscaley = (*object).getScale().getY() * scaleY;
		double newscalez = (*object).getScale().getZ() * scaleZ;
		(*object).setScale(newscalex, newscaley, newscalez);

		glScaled(newscalex, newscaley, newscalez);
	}
}
