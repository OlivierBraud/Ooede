#include "Material.h"

Material::Material(void)
{
	ambient = new float[4];
	diffuse = new float[4];
	specular = new float[4];

	ambient[0] = (float).2, ambient[1] = (float).2, ambient[2] = (float).2, ambient[3] = 1.;
	diffuse[0] = (float).8, diffuse[1] = (float).8, diffuse[2] = (float).8, diffuse[3] = 1.;
	specular[0] = 1., specular[1] = 1., specular[2] = 1., specular[3] = 1.;
}

Material::Material(const Material & m)
{
	if(&m != this){
		ambient = new float[4];
		diffuse = new float[4];
		specular = new float[4];
		for(unsigned int i=0; i<4; i++){
			ambient[i] = m.ambient[i];
			diffuse[i] = m.diffuse[i];
			specular[i] = m.specular[i];
		}
	}
}

Material & Material::operator=(const Material & m)
{
	if(&m != this){
		for(unsigned int i=0; i<4; i++){
			ambient[i] = m.ambient[i];
			diffuse[i] = m.diffuse[i];
			specular[i] = m.specular[i];
		}
	}
	return * this;
}

Material::~Material(void)
{
	delete ambient;
	delete diffuse;
	delete specular;
}

