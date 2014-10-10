#include "Face.h"


Face::Face(void)
{
	textureMapping = std::vector<Point>();
	points = std::vector<Point>();
}

Face::Face(Point & p1, Point & p2, Point & p3)
{
	textureMapping = std::vector<Point>();
	points = std::vector<Point>();
	points.push_back(p1);
	points.push_back(p2);
	points.push_back(p3);
}

Face::Face(Point & p1, Point & p2, Point & p3, Point & p4)
{
	textureMapping = std::vector<Point>();
	points = std::vector<Point>();
	points.push_back(p1);
	points.push_back(p2);
	points.push_back(p3);
	points.push_back(p4);
}

Face::Face(const Face & f)
{
	if(this != & f){
		points = std::vector<Point>();
		textureMapping = std::vector<Point>();
		for(unsigned int i = 0; i < f.points.size(); i++){
			points.push_back(f.points[i]);
		}
		for(unsigned int i = 0; i < f.textureMapping.size(); i++){
			textureMapping.push_back(f.textureMapping[i]);
		}
	}
}

Face & Face::operator=(const Face & f)
{
	if(this != & f){
		points.clear();
		textureMapping.clear();
		for(unsigned int i = 0; i < f.getPointsCount(); i++){
			points.push_back(f.points[i]);
		}
		for(unsigned int i = 0; i < f.textureMapping.size(); i++){
			textureMapping.push_back(f.textureMapping[i]);
		}
	}
	return * this;
}

Point & Face::operator[](unsigned int i)
{
	try{
		return points[i];
	}
	catch(std::exception e){
		throw e;
	}
}

void Face::rescale(const Point & newsize){
	for(unsigned int i = 0; i<points.size(); i++){
		points[i] = points[i] * newsize;
	}
}

void Face::rotate(double angle, Point & axis){
	double c = cos(angle);
	double s = sin(angle);
	double ux = axis.getX();
	double uy = axis.getY();
	double uz = axis.getZ();
	double ux2 = axis.getX() * axis.getX();
	double uy2 = axis.getY() * axis.getY();
	double uz2 = axis.getZ() * axis.getZ();
	for(unsigned int i = 0; i<points.size();i++){
		double vx = 
			(ux2 + (1 - ux2) * c) * points[i].getX() + 
			(ux * uy * (1 - c) - uz * s) * points[i].getY() + 
			(ux * uz * (1 - c) + uy * s) * points[i].getZ();
		double vy = 
			(ux * uy * (1 - c) + uz * s) * points[i].getX() + 
			(uy2 + (1 - uy2) * c) * points[i].getY() + 
			(uy * uz * (1 - c) - ux * s) * points[i].getZ();
		double vz = 
			(ux * uz * (1 - c) - uy * s) * points[i].getX() + 
			(uy * uz * (1 - c) + ux * s) * points[i].getY() + 
			(uz2 + (1 - uz2) * c) * points[i].getZ();
		points[i].setCoordinates(vx,vy,vz);
	}
}

unsigned int Face::getPointsCount(void) const
{
	return points.size();
}

void Face::draw(void)
{
	if(getPointsCount()>3){
		glBegin(GL_QUADS);
	}
	else{
		glBegin(GL_TRIANGLES);
	}
	for(unsigned int i = 0; i < points.size(); i++){
		if(textureMapping.size()==points.size()){
			glTexCoord2d(textureMapping[i].getX(), textureMapping[i].getY()); 
		}
		glVertex3d(points[i].getX(), points[i].getY(), points[i].getZ());
	}
	glEnd();
	glFlush();
}

Point Face::getGravityCenter(){
	double x = 0., y = 0., z = 0.;
	unsigned int size = points.size();
	for(unsigned int i=0; i<size; i++){
		x += points[i].getX();
		y += points[i].getY();
		z += points[i].getZ();
	}
	return Point(x/size, y/size, z/size);
}

void Face::addMapping(Point & p){
	if(textureMapping.size()<points.size()){
		textureMapping.push_back(p);
	}
}

Face::~Face(void)
{
	points.~vector();
	textureMapping.~vector();
}
