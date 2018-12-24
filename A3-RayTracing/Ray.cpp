#include "Ray.h"
#include <math.h>
#include <iostream>

using namespace std;

Ray::Ray() {}
Ray::~Ray() {}

Ray::Ray(Vector o, Vector d) {
	this->origin = o;
	this->direction = d;
}

void Ray::setO(Vector o) {
	this->origin = o;
}

void Ray::setD(Vector d) {
	this->direction = d;
}

Vector Ray::getO() {
	return this->origin;
}

Vector Ray::getD() {
	return this->direction;
}

Vector Ray::getV(float r) {
	float vx = origin.x + direction.x * r;
	float vy = origin.y + direction.y * r;
	float vz = origin.z + direction.z * r;
	Vector v = Vector(vx, vy, vz);

	return v;
}
