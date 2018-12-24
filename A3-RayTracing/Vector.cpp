#include "Vector.h"
#include <iostream>
#include <math.h>

using namespace std;

Vector::Vector(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector::Vector() {}
Vector::~Vector() {}

float Vector::dot(Vector a) { 
	float d = (x * a.x) + (y * a.y) + (z * a.z);
	
	return d;
}

Vector Vector::cross(Vector a) { 
	float cx = (y * a.z) - (z * a.y);
	float cy = (z * a.x) - (x * a.z);
	float cz = (x * a.y) - (y * a.x);
	Vector c = Vector(cx, cy, cz);

	return c;
}

Vector Vector::normal() {
	float length = sqrt(x*x + y*y + z*z);
	float nx = x / length;
	float ny = y / length;
	float nz = z / length;
	Vector n = Vector(nx, ny, nz);

	return n;
}

float Vector::distance(Vector a) {
	float d = sqrt(pow((x - a.x), 2) + pow((y - a.y), 2) + pow((z - a.z), 2));

	return d;
}
