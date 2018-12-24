#ifndef _PHONG_H_
#define _PHONG_H_

#include "Vector.h"
#include "Ray.h"
#include "Color.h"
#include <math.h>

class Phong {
private:
	Color diffuse;
	Color specular;
	float shininess;
	Vector lightD;
	Color lightC;

public:
	Phong();
	~Phong();
	Phong(Color diffuse,Color specular,float shininess,Vector lightD, Color lightC);
	virtual Color sample(Ray r, Vector v, Vector n);
};


#endif
