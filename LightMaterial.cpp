#include "LightMaterial.h"


LightMaterial::LightMaterial(void):Material()
{
	globalIntensity = 127;
	ambient[0] = 0., ambient[1] = 0., ambient[2] = 0., ambient[3] = 1.;
	diffuse[0] = 1., diffuse[1] = 1., diffuse[2] = 1., diffuse[3] = 1.;
}

LightMaterial::LightMaterial(const LightMaterial & m):Material(m)
{
	if(&m != this){
		globalIntensity = m.globalIntensity;
	}
}

LightMaterial & LightMaterial::operator=(const LightMaterial & m){
	if(&m != this){
		globalIntensity = m.globalIntensity;
		for(unsigned int i=0; i<4; i++){
			ambient[i] = m.ambient[i];
			diffuse[i] = m.diffuse[i];
			specular[i] = m.specular[i];
		}
	}
	return * this;
}

LightMaterial::~LightMaterial(void)
{
}