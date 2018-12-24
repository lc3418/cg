#ifndef _INTERSECT_H_
#define _INTERSECT_H_

#include "Vector.h"

struct Intersect 
{
	bool intersected = false;
	Vector position; //vector that ray and Sphere are intersected
	Vector Pnormal; //normal vector at vector position
	float distance ; //distance between position and the origin of the ray
};

#endif 

