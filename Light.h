#pragma once
#ifndef LIGHT_H
#define LIGHT_H

#include "TransformableObject.h"
#include "LightMaterial.h"

class Light:public TransformableObject
{
public:
	Light(void);
	Light(std::string newName, Point & center, Point & dir);
	Light(const Light &);
	~Light(void);

	Light & operator=(const Light &);

	void draw(void);

	void setName(std::string newName){name = newName;};
	std::string & getName(void){return name;};
	Point & getCenterPosition(void){return centerPosition;};
	void setCenterPosition(Point & newcenter){centerPosition = newcenter;};
	double getAngle(){return angle;};
	void setAngle(double newangle){angle = newangle;};
	float getAttenuation(){return attenuation;};
	void setAttenuation(float newaattenuation){attenuation = newaattenuation;};
	Point & getScale(){return scale;};
	void setScale(double x, double y, double z){scale.setCoordinates(x,y,z);};
	int getSpreadAngle(void){return spreadAngle;};
	int setSpreadAngle(int newangle){spreadAngle = newangle;};
	LightMaterial & getMaterial(void){return material;};

private:
	char id;
	Point centerTarget;
	static char lightNumber;
	LightMaterial material;
	int spreadAngle;
	float attenuation;
};
#endif