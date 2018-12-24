#include "Camera.h"

#define _USE_MATH_DEFINES
#include <math.h>

Camera::Camera() {};
Camera::~Camera() {};

Camera::Camera(Vector eye, Vector front, Vector up1, float viewAngle) {
	this->eye = eye;
	this->front = front;
	this->up1 = up1;
	this->right = front.cross(up1);
	this->up = right.cross(front);
	this->viewAngle = viewAngle;
	this->transform = tan((viewAngle / 2)*(M_PI / 180)) * 2;
}

Ray Camera::getRay(float x, float y) {
	float x1 = (x)*transform;
	float y1 = (y)*transform;
	Vector temp1 = Vector(right.x * x1,right.y * x1,right.z);
	Vector temp2 = Vector(up.x * y1, up.y * y1, up.z);
	Vector d = Vector((front.x + temp1.x + temp2.x), (front.y + temp1.y + temp2.y), (front.z + temp1.z + temp2.z));
	Vector nd = d.normal();
	Ray r = Ray(eye, nd);

	return r;

}