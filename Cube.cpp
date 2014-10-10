#include "Cube.h"


Cube::Cube(void):Mesh()
{
	name = "Cube";
	materials.push_back(FaceMaterial());
	faces.push_back(face_materialindex(
		Face(Point(-1,-1,1), Point(-1,-1,-1), Point(1,-1,-1), Point(1,-1,1)),
		0));
	faces.push_back(face_materialindex(
		Face(Point(1,-1,1), Point(1,1,1), Point(-1,1,1), Point(-1,-1,1)),
		0));
	faces.push_back(face_materialindex(
		Face(Point(-1,1,1), Point(-1,1,-1), Point(-1,-1,-1), Point(-1,-1,1)),
		0));
	faces.push_back(face_materialindex(
		Face(Point(1,1,-1), Point(1,-1,-1), Point(-1,-1,-1), Point(-1,1,-1)),
		0));
	faces.push_back(face_materialindex(
		Face(Point(1,1,1), Point(1,-1,1), Point(1,-1,-1), Point(1,1,-1)),
		0));
	faces.push_back(face_materialindex(
		Face(Point(1,1,1), Point(1,1,-1), Point(-1,1,-1), Point(-1,1,1)),
		0));
}

Cube::Cube(const Cube & c):Mesh(c)
{
}

Cube::~Cube(void)
{
}

