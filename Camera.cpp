#include "Camera.h"

Camera::Camera(void)
{
	name = "Camera";
	angle = 0;
	scale = Point(1.,1.,1.);
	centerPosition = Point(5.,5.,5.);
	centerOfView = Point(0.,0.,0.);
	verticalAxis = Point::AXIS_Y;
}

Camera::Camera(std::string newname, Point & position, Point & view, const char vertical){
	name = newname;
	angle = 0;
	scale = Point(1.,1.,1.);
	centerPosition = position;
	centerOfView = view;
	verticalAxis = vertical;
}

Camera::Camera(const Camera & camera){
	if(this!=&camera){
		name = camera.name;
		angle = camera.angle;
		scale = camera.scale;
		centerOfView=camera.centerOfView;
		centerPosition=camera.centerPosition;
		verticalAxis = camera.verticalAxis;
	}
}

Camera & Camera::operator=(const Camera & camera){
	if(this!=&camera){
		name = camera.name;
		angle = camera.angle;
		scale = camera.scale;
		centerOfView=camera.centerOfView;
		centerPosition=camera.centerPosition;
		verticalAxis = camera.verticalAxis;
	}
	return * this;
}

void Camera::draw(){
	gluLookAt(centerPosition.getX(), centerPosition.getY(), centerPosition.getZ(), 
		centerOfView.getX(), centerOfView.getY(), centerOfView.getZ(),
		verticalAxis==Point::AXIS_X, verticalAxis==Point::AXIS_Y, verticalAxis==Point::AXIS_Z);
}

Camera::~Camera(void)
{
	name.clear();
	centerPosition.~Point();
	centerOfView.~Point();
}
