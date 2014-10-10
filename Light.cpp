#include "Light.h"

char Light::lightNumber = 0;

Light::Light(void){
	id = lightNumber;
	lightNumber++;
	angle = 0;
	attenuation = 0.;
	spreadAngle = 50;
	scale = Point(1.,1.,1.);
	centerPosition = Point(5.,5.,5.);
	centerTarget = Point(0.,0.,0.);
	name = "Light"+id;
	material = LightMaterial();
}

Light::Light(std::string newName, Point & center, Point & dir){
	id = lightNumber;
	lightNumber++;
	angle = 0;
	attenuation = 0.;
	spreadAngle = 180;
	scale = Point(1.,1.,1.);
	centerTarget = dir;
	name = newName;
	centerPosition = center;
	material = LightMaterial();
}

Light::Light(const Light & l){
	if(&l!=this){
		id = lightNumber;
		lightNumber++;
		angle = l.angle;
		scale = l.scale;
		name = l.name;
		attenuation = l.attenuation;
		centerPosition = l.centerPosition;
		material = l.material;
		spreadAngle = l.spreadAngle;
	}
}

Light & Light::operator=(const Light & l){
	if(&l!=this){
		id = l.id;
		angle = l.angle;
		scale = l.scale;
		name = l.name;
		attenuation = l.attenuation;
		centerPosition = l.centerPosition;
		material = l.material;
		spreadAngle = l.spreadAngle;
	}
	return * this;
}

void Light::draw(void){
	glEnable(GL_LIGHT0+id);
	glLightf(GL_LIGHT0+id,GL_QUADRATIC_ATTENUATION, attenuation);
	glLightfv(GL_LIGHT0+id, GL_POSITION, centerPosition.getFloatArray4(1.));
	glLightfv(GL_LIGHT0+id, GL_DIFFUSE, material.getDiffuse());
	glLightfv(GL_LIGHT0+id, GL_AMBIENT, material.getAmbient());
	glLightfv(GL_LIGHT0+id, GL_SPECULAR, material.getSpecular());
	glLighti(GL_LIGHT0+id, GL_SPOT_EXPONENT, material.getGlobalIntensity());
	glLighti(GL_LIGHT0+id, GL_SPOT_CUTOFF, spreadAngle);
	glLightfv(GL_LIGHT0+id, GL_SPOT_DIRECTION, (centerTarget-centerPosition).getFloatArray3());
}

Light::~Light(void){
	centerPosition.~Point();
	material.~LightMaterial();
	name.clear();
	lightNumber--;
}
