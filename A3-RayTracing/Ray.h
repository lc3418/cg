#ifndef _RAY_H_
#define _RAY_H_

#include "Vector.h"

class Ray {
private:
	Vector origin;
	Vector direction;

public:
	Ray();
	Ray(Vector o, Vector d);
	~Ray();

	void setO(Vector o); //set origin
	void setD(Vector d); //set direction
	Vector getO(); //get origin
	Vector getD(); //get direction
	Vector getV(float r); //get a point on the ray


};

#endif
