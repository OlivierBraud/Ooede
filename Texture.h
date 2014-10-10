#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H

#include <Windows.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <string>

#ifndef GL_CLAMP_TO_EDGE
#define GL_CLAMP_TO_EDGE 0x812F
#endif

class Texture{
public:
	Texture(void);
	Texture(std::string & fileName);
	Texture(const Texture & t);
	~Texture(void);

	Texture & operator=(const Texture & t);

	void draw(void);

	int getId(void){return id;};
	
private:
	std::string fileName;
	int id;
private:
	GLuint loadTexture(const char * filename,bool useMipMap = true);
	SDL_Surface * flipSurface(SDL_Surface * surface);
};
#endif

