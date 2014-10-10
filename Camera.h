#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include "StaticObject.h"


class Camera:public StaticObject
{
public:
	Camera(void);
	Camera(const Camera &);
	Camera(std::string name, Point & position, Point & newCenter, const char vertical);
	~Camera(void);

	Camera & operator=(const Camera &);

	void draw();

	//getters and setters
	void setCenterOfView(Point & newCenter){centerOfView=newCenter;};
	Point & getCenterOfView(void){return centerOfView;};
	void setVerticalAxis(const char newVertical){verticalAxis=newVertical;};
	char getVerticalAxis(void){return verticalAxis;};
	std::string & getName() {return name;};
	void setName(std::string newName){name = newName;};
	Point & getCenterPosition(void){return centerPosition;};
	void setCenterPosition(Point & newcenter){centerPosition = newcenter;};
	double getAngle(){return angle;};
	void setAngle(double newangle){angle = newangle;};
	Point & getScale(){return scale;};
	void setScale(double x, double y, double z){scale.setCoordinates(x,y,z);};
private:
	Point centerOfView;
	char verticalAxis;
};
#endif
