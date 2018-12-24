#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Ray.h"
#include "Vector.h"

class Camera{
private:
	Vector eye;
	Vector front;
	Vector right;
	Vector up;
	Vector up1;
	float viewAngle;
	float transform;

public:
	Camera();
	~Camera();
	
	Camera(Vector eye, Vector front, Vector up, float viewAngle);
	Ray getRay(float x, float y); //calculate a ray from eye to one screen pixel
};


#endif
