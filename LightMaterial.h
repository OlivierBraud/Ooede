#pragma once
#ifndef LIGHTMATERIAL_H
#define LIGHTMATERIAL_H

#include "Material.h"

class LightMaterial:public Material
{
public:
	LightMaterial(void);
	LightMaterial(const LightMaterial &);
	~LightMaterial(void);

	LightMaterial & operator=(const LightMaterial & m);

	void setGlobalIntensity(int intensity){globalIntensity = intensity;};
	int getGlobalIntensity(void){return globalIntensity;};
private:
	int globalIntensity;
};
#endif
