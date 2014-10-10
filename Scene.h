#pragma once
#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <string>

#include "Object.h"
#include "Mesh.h"
#include "Camera.h"
#include "Light.h"
#include "Transformation.h"

class Scene
{
public:
	Scene(void);
	Scene(std::string & name, double ratio);
	Scene(const Scene &);
	~Scene(void);
	void initScript(void);

	Scene & operator=(const Scene &);
	Object * operator[](unsigned int i);

	Camera * getCamera(unsigned int i);
	Mesh * getMesh(unsigned int i);
	Light * getLight(unsigned int i);
	std::string & getName(){return name;};
	unsigned int getMeshCount();

	void setName(std::string & newName){name = newName;};
	void setActiveCamera(char cameraNumber);
	void addCamera(Camera * camera);
	void addLight(Light * light);
	void addMesh(Mesh * mesh);
	void removeObject(unsigned int);
	void transformObject(Transformation *);

	void draw(void);
private:
	std::string name;
	char currentCamera;
	double ratio;
	std::vector<Transformation *> transformations;
	std::vector<Object *> objects;
public:
	static const char CAMERA_MAX_NUMBER = 8;
	static const char LIGHT_MAX_NUMBER = 8;
};
#endif

