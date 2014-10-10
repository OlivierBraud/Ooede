#pragma once
#ifndef MATERIAL_H
#define MATERIAL_H

#include <Windows.h>
#include <gl/GL.h>


class Material
{
public:
	Material(void);
	Material(const Material & m);
	~Material(void);

	Material & operator=(const Material & m);

	void setDiffuse(float v1, float v2, float v3, float v4){
		diffuse[0]=v1, diffuse[1]=v2, diffuse[2]=v3, diffuse[3]=v4;
	}
	void setSpecular(float v1, float v2, float v3, float v4){
		specular[0]=v1, specular[1]=v2, specular[2]=v3, specular[3]=v4;
	}
	void setAmbient(float v1, float v2, float v3, float v4){
		ambient[0]=v1, ambient[1]=v2, ambient[2]=v3, ambient[3]=v4;
	}
	float * getDiffuse(){return diffuse;};
	float * getAmbient(){return ambient;};
	float * getSpecular(){return specular;};

protected:
	float * ambient;
	float * specular;
	float * diffuse;
};
#endif

