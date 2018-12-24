#include "CheckerBoard.h"

CheckerBoard::CheckerBoard() {};
CheckerBoard::~CheckerBoard() {};

CheckerBoard::CheckerBoard(float size) {
	this->size = size;
	//this->reflect = reflect;
}

Color CheckerBoard::sample(Ray r, Vector v, Vector n) {
	float temp = floor(v.x * size);
	float temp2 = floor(v.z * size);
	float temp3 = abs(temp + temp2);
	temp3 = fmod(temp3, 2);
	if (temp3 < 1) {
		return Color(1, 1, 1);
	}
	if (temp3 >= 1) {
		return Color(0, 0, 0);
	}	
}