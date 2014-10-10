#pragma once
#ifndef MESHMATERIAL_H
#define MESHMATERIAL_H

#include "Material.h"
#include "Texture.h"
#include "Color.h"

class FaceMaterial:public Material
{
public:
	FaceMaterial(void);
	FaceMaterial(const FaceMaterial &);
	~FaceMaterial(void);

	FaceMaterial & operator=(const FaceMaterial & m);

	void applyMaterial(void);

	float * getEmission(){return emission;};
	int getShininess(){return shininess;};
	void setShininess(int v1){shininess=v1;}
	void setTexture(Texture & t){texture=t;}
	void setColor(Color & c){color=c;};
	Color & getColor(void){return color;};
	unsigned char getAlpha(void){return alpha;};
	void setAlpha(unsigned char newAlpha){alpha = newAlpha;}; 
	void setEmission(float v1, float v2, float v3, float v4){
		emission[0]=v1, emission[1]=v2, emission[2]=v3, emission[3]=v4;
	}

private:
	int shininess;
	float * emission;
	Texture texture;
	Color color;
	unsigned char alpha;
};
#endif
