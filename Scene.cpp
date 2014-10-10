#include "Scene.h"


Scene::Scene(void)
{
	ratio = (double)800/600;
	initScript();
	name = "Scene";
	transformations = std::vector<Transformation *>();
	objects = std::vector<Object *>();
	objects.push_back(new Camera());
	currentCamera = 0;
	for(unsigned int i=1; i<CAMERA_MAX_NUMBER; i++){
		objects.push_back(NULL);
	}
	objects.push_back(new Light());
	for(unsigned int i=CAMERA_MAX_NUMBER+1; i<CAMERA_MAX_NUMBER+LIGHT_MAX_NUMBER; i++){
		objects.push_back(NULL);
	}
}

Scene::Scene(std::string & newName, double newratio){
	ratio = newratio;
	initScript();
	name = newName;
	transformations = std::vector<Transformation *>();
	objects = std::vector<Object *>();
	objects.push_back(new Camera());
	currentCamera = 0;
	for(unsigned int i=1; i<CAMERA_MAX_NUMBER; i++){
		objects.push_back(NULL);
	}
	objects.push_back(new Light());
	for(unsigned int i=CAMERA_MAX_NUMBER+1; i<CAMERA_MAX_NUMBER+LIGHT_MAX_NUMBER; i++){
		objects.push_back(NULL);
	}
}

Scene::Scene(const Scene & scene){
	if(&scene!=this){
		ratio = scene.ratio;
		initScript();
		name = scene.name;
		objects = std::vector<Object *>();
		for(unsigned int i=0; i<objects.size(); i++){
			objects.push_back(scene.objects[i]);
		}
		transformations = std::vector<Transformation *>();
		for(unsigned int i=0; i<transformations.size(); i++){
			transformations.push_back(scene.transformations[i]);
		}
	}
}

void Scene::initScript(){
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f) ;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70., ratio, 1., 200.); 

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_TEXTURE_2D);
}

Scene & Scene::operator=(const Scene & scene){
	if(&scene!=this){
		for(unsigned int i=0; i<objects.size(); i++){
			delete objects[i];
			objects.erase(objects.begin()+i);
		}
		name = scene.name;
		objects = std::vector<Object *>();
		for(unsigned int i=0; i<objects.size(); i++){
			objects.push_back(scene.objects[i]);
		}
		transformations = std::vector<Transformation *>();
		for(unsigned int i=0; i<transformations.size(); i++){
			transformations.push_back(scene.transformations[i]);
		}
	}
	return * this;
}

Object * Scene::operator[](unsigned int i){
	return objects[i];
}

Camera * Scene::getCamera(unsigned int i){
	if(i<CAMERA_MAX_NUMBER){
		Camera * camera = dynamic_cast<Camera*>(objects[i]);
		return camera;
	}
	return NULL;
}

Mesh * Scene::getMesh(unsigned int i){	
	Mesh * mesh = dynamic_cast<Mesh*>(objects[CAMERA_MAX_NUMBER+LIGHT_MAX_NUMBER+i]);
	return mesh;
}

unsigned int Scene::getMeshCount(){
	return objects.size() - CAMERA_MAX_NUMBER - LIGHT_MAX_NUMBER;
}

Light * Scene::getLight(unsigned int i){
	if(i<LIGHT_MAX_NUMBER){
		Light * light = dynamic_cast<Light*>(objects[CAMERA_MAX_NUMBER+i]);
		return light;
	}
	return NULL;
}

void Scene::draw(){
	for(unsigned int i=0; i<LIGHT_MAX_NUMBER; i++){
		glDisable(GL_LIGHT0+i);
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	(*objects[currentCamera]).draw();

	for(unsigned int i=CAMERA_MAX_NUMBER; i<objects.size(); i++){
		if(objects[i]!=NULL){
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			for(unsigned int j=0; j<transformations.size(); j++){
				if(objects[i]==(*transformations[j]).getObject()){
					(*transformations[j]).transform();
					delete transformations[j];
					transformations.erase(transformations.begin()+j);
				}
			}
			(*objects[i]).draw();
			glPopMatrix();
		}
	}
}

void Scene::addCamera(Camera * camera){
	for(unsigned int i=0; i<CAMERA_MAX_NUMBER; i++){
		if(objects[i]==NULL){
			objects.insert(objects.begin()+i, camera);
			return;
		}
	}
}

void Scene::addMesh(Mesh * mesh){
	objects.push_back(mesh);
}

void Scene::addLight(Light * light){
	for(unsigned int i=CAMERA_MAX_NUMBER; i<CAMERA_MAX_NUMBER+LIGHT_MAX_NUMBER; i++){
		if(objects[i]==NULL){
			objects.insert(objects.begin()+i, light);
			return;
		}
	}
}

void Scene::removeObject(unsigned int i){
	if(i>0 && i<objects.size()){
		delete objects[i];
		objects.erase(objects.begin()+i);
	}
}

void Scene::transformObject(Transformation * transformation){
	transformations.push_back(transformation);
}

Scene::~Scene(void)
{
	for(unsigned int i=0; i<transformations.size(); i++){
		delete transformations[i];
	}
	transformations.~vector();
	for(unsigned int i=0; i<objects.size(); i++){
		delete objects[i];
	}
	objects.~vector();
}
