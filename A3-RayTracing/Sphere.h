#ifndef _SPHERE_H_
#define _SPHERE_H_
#include "Vector.h"
#include "Ray.h"
#include "Intersect.h"
#include "Phong.h"

class Sphere {
private:
	Vector center;
	float radius;

public:
	Sphere();
	~Sphere();

	Phong ph;
	Sphere(Vector center, float radius);
	void setC(Vector c);
	void setR(float r);
	Vector getC();
	float getR();
	Vector getN(Vector point); //get the normal vector of a point on sphere

	Intersect intersect(Ray r); //get the parameter t which makes the ray and the sphere intersect

	
	//Intersect ShadowIntersect();
};


#endif 

