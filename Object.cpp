#include "Object.h"

void Object::move(double x, double y, double z){
	transformationsNumber++;
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	centerPosition.setCoordinates(centerPosition.getX()+x,centerPosition.getY()+y,centerPosition.getZ()+z);
	glTranslated(x,y,z);
}



void Object::draw(){
}

void Object::resetTransformations(){
	if(transformationsNumber>0){
		for(unsigned int i=0; i < transformationsNumber; i++){
			transformationsNumber--;
			glMatrixMode(GL_MODELVIEW);
			glPopMatrix();
		}
	}
}

Object::~Object(void)
{
	name.clear();
	centerPosition.~Point();
}
