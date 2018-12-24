#ifndef _PLANE_H_
#define _PLANE_H_
#include "Ray.h"
#include "Vector.h"
#include "Intersect.h"
//#include "Material.h"
#include "CheckerBoard.h"


class Plane {
private:
	Vector normal;
	float distance; //distance between origin
	//Material m;
public:
	CheckerBoard ch;
	Plane();
	~Plane();
	Plane(Vector normal, float distance);
	Intersect intersect(Ray r);
	Intersect shadowIntersect(Ray r);
};


#endif

