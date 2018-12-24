#ifndef _COLOR_H_
#define _COLOR_H_
#include <iostream>
#include <math.h>


class Color {

public:
	float r;
	float g;
	float b;
	Color();
	~Color();
	Color(float r, float g, float b);
	Color add(Color c);
	Color mult(float m);
	Color adjust(Color c);
	void saturate();

};

#endif