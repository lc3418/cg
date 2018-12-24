#include "Sphere.h"
#include <math.h>
#include <iostream>


using namespace std;

Sphere::Sphere() {};
Sphere::~Sphere() {};

Sphere::Sphere(Vector center, float radius) {
	this->center = center;
	this->radius = radius;
}

void Sphere::setC(Vector c) {
	this->center = c;
}

void Sphere::setR(float r) {
	this->radius = r;
}

Vector Sphere::getC() {
	return this->center;
}

float Sphere::getR() {
	return this->radius;
}

Vector Sphere::getN(Vector p) {
	float nx = p.x - center.x;
	float ny = p.y - center.y;
	float nz = p.z - center.z;
	Vector n = Vector(nx, ny, nz);

	return n;
}

Intersect Sphere::intersect(Ray r) {
	Vector origin = r.getO();
	Vector direction = r.getD();
	float o = origin.x - center.x;
	float p = origin.y - center.y;
	float q = origin.z - center.z;
	Vector v = Vector(o, p, q);
	float temp = v.dot(v) - pow(radius, 2);
	float temp2 = direction.dot(v);
	Intersect i = Intersect();

	/*float lamda = pow((2 * direction.x * o + 2 * direction.y*p + 2 * direction.z*q), 2) +
		4 * (pow(direction.x, 2) + pow(direction.y, 2) + pow(direction.z, 2)) *
		(pow(radius, 2) - pow(o, 2) - pow(p, 2) - pow(q, 2));
	if (lamda < 0) {

	}
	if (lamda = 0) {

	}
	if (lamda > 0) {

	}*/

	if (temp2 < 0) {
		float dis = pow(temp2, 2) - temp;
		if (dis > 0) {
			i.intersected = true;
			i.distance = -temp2 - sqrt(dis);
			i.position = r.getV(i.distance);
			float nx = i.position.x - center.x;
			float ny = i.position.y - center.y;
			float nz = i.position.z - center.z;
			Vector n = Vector(nx, ny, nz);
			i.Pnormal = n.normal();
		}
	}
	return i;	
}

//Intersect Sphere::ShadowIntersect() {

//}