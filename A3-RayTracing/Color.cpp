#include "Color.h"
using namespace std;

Color::Color() {};
Color::~Color() {};
Color::Color(float r, float g, float b) {
	this->r = r;
	this->g = g;
	this->b = b;
}

Color Color::add(Color c) {
	float tr = r + c.r;
	float tg = g + c.g;
	float tb = b + c.b;
	Color a = Color(tr,tg,tb);

	return a;
}

Color Color::mult(float m) {
	float tr = r * m;
	float tg = g * m;
	float tb = b * m;
	Color c = Color(tr, tg, tb);

	return c;
}

Color Color::adjust(Color c) {
	return Color(r*c.r, g*c.g, b*c.b);
}

void Color::saturate() {
	if (r > 1) {
		r = 1;
	}
	else {
		r = r;
	}

	if (g > 1) {
		g = 1;
	}
	else {
		g = g;
	}

	if (b > 1) {
		b = 1;
	}
	else {
		b = b;
	}
}
