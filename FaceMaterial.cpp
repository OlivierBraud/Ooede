#include "FaceMaterial.h"


FaceMaterial::FaceMaterial(void):Material()
{
	emission = new float[4];
	shininess = 100;
	texture = Texture();
	color = Color();
	alpha = 255;
	emission[0] = 0., emission[1] = 0., emission[2] = 0., emission[3] = 1.;
	shininess = 0;
}

FaceMaterial::FaceMaterial(const FaceMaterial & m):Material(m){
	if(&m != this){
		emission = new float[4];
		shininess = m.shininess;
		texture = m.texture;
		color = m.color;
		alpha = m.alpha;
		for(unsigned int i=0; i<4; i++){
			ambient[i] = m.ambient[i];
			diffuse[i] = m.diffuse[i];
			specular[i] = m.specular[i];
			emission[i] = m.emission[i];
		}
	}
}

FaceMaterial & FaceMaterial::operator=(const FaceMaterial & m){
	if(&m != this){
		for(unsigned int i=0; i<4; i++){
			ambient[i] = m.ambient[i];
			diffuse[i] = m.diffuse[i];
			specular[i] = m.specular[i];
			emission[i] = m.emission[i];
		}
		shininess = m.shininess;
		texture = m.texture;
		alpha = m.alpha;
		color = m.color;
	}
	return * this;
}

void FaceMaterial::applyMaterial(void){
	glColor4ub(color.getRed(), color.getGreen(), color.getBlue(), alpha);
	glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glBindTexture(GL_TEXTURE_2D, texture.getId());
}

FaceMaterial::~FaceMaterial(void)
{
	color.~Color();
	delete emission;
}