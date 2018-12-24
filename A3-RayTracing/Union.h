#ifndef _UNION_H_
#define _UNION_H_
#include "Ray.h"
#include "Plane.h"
#include "Sphere.h"
#include "Intersect.h"


using namespace std;

class Union {
private:
	Plane p;
	Sphere s;
	//vector<CObject>
public:
	Union();
	~Union();
	Union(Plane p ,Sphere s);
	Intersect intersect(Ray r);
};


#endif