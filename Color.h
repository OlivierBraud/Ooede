#pragma once
#ifndef COLOR_H
#define COLOR_H

class Color
{
public:
	Color(void);
	Color(int r, int v, int b);
	Color(const Color & color);
	Color(int colorConst);
	~Color(void);

	Color & operator=(const Color &);

	unsigned char getRed(void){return red;}
	unsigned char getGreen(void){return green;}
	unsigned char getBlue(void){return blue;}

private:
	unsigned char red;
	unsigned char green;
	unsigned char blue;
public:
	static const int COLOR_WHITE = 0;
	static const int COLOR_BLACK = 1;
	static const int COLOR_BLUE = 2;
	static const int COLOR_RED = 3;
	static const int COLOR_GREEN = 4;
	static const int COLOR_PURPLE = 5;
	static const int COLOR_YELLOW = 6;
	static const int COLOR_CYAN = 7;
};
#endif
