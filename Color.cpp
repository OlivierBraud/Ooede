#include "Color.h"


Color::Color(void)
{
	red = 255;
	green = 255;
	blue = 255;
}

Color::Color(int colorConst)
{
	switch(colorConst){
	case COLOR_WHITE:
		red = 255;
		blue = 255;
		green = 255;
		break;
	case COLOR_BLACK:
		red = 0;
		blue = 0;
		green = 0;
		break;
	case COLOR_BLUE:
		red = 0;
		blue = 255;
		green = 0;
		break;
	case COLOR_GREEN:
		red = 0;
		blue = 0;
		green = 255;
		break;
	case COLOR_RED:
		red = 255;
		blue = 0;
		green = 0;
		break;
	case COLOR_PURPLE:
		red = 255;
		blue = 255;
		green = 0;
		break;
	case COLOR_YELLOW:
		red = 255;
		blue = 0;
		green = 255;
		break;
	case COLOR_CYAN:
		red = 0;
		blue = 255;
		green = 255;
		break;
	}
}

Color::Color(const Color & color)
{
	red = color.red;
	green = color.green;
	blue = color.blue;
}


Color::Color(int r, int g, int b)
{
	red = r;
	green = g;
	blue = b;
}

Color & Color::operator=(const Color & color){
	if(this != & color){
		red = color.red;
		blue = color.blue;
		green = color.green;
	}
	return * this;
}

Color::~Color(void)
{
}
