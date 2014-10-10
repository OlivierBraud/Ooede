#pragma once
#ifndef MESH_H
#define MESH_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>

#include "TransformableObject.h"
#include "Face.h"
#include "FaceMaterial.h"

struct face_materialindex{
	face_materialindex(Face &, unsigned int);
	~face_materialindex(void);

	Face face;
	unsigned int materialIndex;
};

//--------------------------------------------------

class Mesh:public TransformableObject
{
public:
	Mesh(void);
	Mesh(std::string, std::string);
	Mesh(const Mesh &);
	~Mesh(void);

	Mesh & operator=(const Mesh &);
	Face & operator[](unsigned int);

	void rescale(const Point & newsize);
	void rotate(double, Point &); 
	void draw();

	std::string & getName() {return name;};
	void setName(std::string newName) {name = newName;};
	Point & getCenterPosition(void){return centerPosition;};
	void setCenterPosition(Point &);
	Point getGravityCenter(void);
	double getAngle(){return angle;};
	void setAngle(double newangle){angle = newangle;};
	Point & getScale(){return scale;};
	void setScale(double x, double y, double z){scale.setCoordinates(x,y,z);};
	FaceMaterial & getMaterial(unsigned int i){return materials[i];};

protected:
	double angle;
	Point scale;
	std::vector<face_materialindex> faces;
	std::vector<FaceMaterial> materials;
private:
	void loadObjFile(std::string, std::string);
};
#endif
