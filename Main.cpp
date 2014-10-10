#include <Windows.h>
#include <SDL/SDL.h>
#include <time.h>
#include "Scene.h"
#include "Mesh.h"
#include "Camera.h"
#include "Rotation.h"
#include "Rescaling.h"
#include "Translation.h"
#include "Material.h"
#include "UvSphere.h"
#include "Cylinder.h"

const int LARGEUR_ECRAN = 800;
const int HAUTEUR_ECRAN = 600;

void randomTree(Scene * s, int maxdepth, int maxBranchPerNode, int currdepth=0, float angle=M_PI/2, double X=0.,double Y=0., double Z = 0.){
	float newangle, newx, newy;
	int branches;
	if(currdepth<=maxdepth){
		branches = (rand() % maxBranchPerNode) + 1;
		s->addMesh(new Cylinder(9));
		if(currdepth>0){
			s->getMesh(s->getMeshCount()-1)->setCenterPosition(Point(X,Y,Z));
			s->getMesh(s->getMeshCount()-1)->rotate(angle, Point(0,0,1));
			s->getMesh(s->getMeshCount()-1)->rescale(Point(0.75,0.75,0.75));
		}
		currdepth++;
		for(float i = -branches/2.f; i<(branches/2.f); i++){
			newangle = (angle + (M_PI/2 * i / branches));
			newx = X-cos(newangle);
			newy = Y+2*sin(angle);
			randomTree(s,maxdepth, maxBranchPerNode, currdepth, newangle, newx, newy,0);
		}
	}
	else{
		return;
	}
}

int main(int argc, char ** argv){
	srand(time(NULL));
	SDL_Event event;

    SDL_Init(SDL_INIT_VIDEO);
    atexit(SDL_Quit);

    SDL_WM_SetCaption("3D", NULL);
    SDL_SetVideoMode(LARGEUR_ECRAN, HAUTEUR_ECRAN, 32, SDL_OPENGL);

	Scene s = Scene();
	//s.getCamera(0)->setCenterPosition(Point(0,5,5));
	//s.addMesh(new UvSphere(9,9));
	//s.addMesh(new Cylinder(9));
	//s.getMesh(0)->rotate(90, Point(0,0,1));
	//randomTree(&s, 6, 1);
	//s.getMesh(0)->rotate(90,Point(1,1,1), Point(0,0,1));
	//s.getLight(0)->getMaterial().setSpecular(0.01,0.01,0.01,1);
	s.addMesh(new Mesh("C:/Users/Olivier/Downloads/liberty bomber.obj", "C:/Users/Olivier/Downloads/liberty bomber.mtl"));
	//s.getMesh(0)->rescale(Point(1.5,1.5,1.5));
	//s.getMesh(0)->setCenterPosition(Point(2.,2.,2.));
	//s.getMesh(0)->getMaterial(0).setColor(Color(Color::COLOR_RED));
	//s.addMesh(new Mesh());


	while(SDL_WaitEvent(&event)){
		switch(event.type){
		case SDL_QUIT:
			exit(0);
			break;
		}
		//s.transformObject(new Rotation(10, Point(0,0,0),Point(0,0,1), s.getMesh(0)));
		//s.transformObject(new Rescaling(1.01,1.01,1.01, s.getMesh(0)));
		//s.transformObject(new Rotation(10, Point(0,0,0),Point(0,1,0), s.getLight(0)));
		//s.transformObject(new Rescaling(1.01,1.01,1.01, s.getMesh(1)));
		s.draw();
		SDL_GL_SwapBuffers();
	}
	return 0;
}