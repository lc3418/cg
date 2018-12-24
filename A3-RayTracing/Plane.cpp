#include "Plane.h"

using namespace std;

Plane::Plane() {};
Plane::~Plane() {};

Plane::Plane(Vector normal, float distance) {
	this->normal = normal;
	this->distance = distance;
}

Intersect Plane::intersect(Ray r) {
	Intersect i = Intersect();
	Vector dir = r.getD();
	float temp = dir.dot(normal);
	if (temp < 0) {
		i.intersected = true;
		Vector temp2 = Vector((r.getO().x-normal.x * distance), (r.getO().y - normal.y * distance), (r.getO().z - normal.z * distance));
		float temp3 = normal.dot(temp2);
		i.Pnormal = normal;
		i.distance = (-temp3) / temp;
		i.position = r.getV(i.distance);
	}
	return i;
}

Intersect Plane::shadowIntersect(Ray r) {
	Intersect i = Intersect();
	float t = (-1 - r.getO().y) / (r.getD().y);
	i.intersected = true;
	i.position = Vector((r.getO().x + t*r.getD().x), (r.getO().y + t * r.getD().y), (r.getO().z + t * r.getD().z));
	i.Pnormal = this->normal;
	i.distance = sqrt(pow((i.position.x - r.getO().x), 2) + pow((i.position.y - r.getO().y), 2) + pow((i.position.z - r.getO().z), 2));
	
	return i;
}