#include "Phong.h"
#include <algorithm>

Phong::Phong() {};
Phong::~Phong() {};

Phong::Phong(Color diffuse, Color specular, float shininess,Vector lightD,Color lightC) {
	this->diffuse = diffuse;
	this->specular = specular;
	this->shininess = shininess;
	this->lightC = lightC;
	this->lightD = lightD;
}

Color Phong::sample(Ray r, Vector v, Vector n) {
	float NdL = n.dot(lightD.normal());
	Color c = diffuse.mult(NdL).add(lightC);
	Vector V = Vector((v.x - r.getO().x),(v.y-r.getO().y),(v.z-r.getO().z)).normal();	
	Vector R = Vector(n.x * 2 * NdL - lightD.x, n.y * 2 * NdL - lightD.y, n.z * 2 * NdL - lightD.z).normal();
	float temp2 = pow(V.dot(R),shininess);
	c = c.add(specular.mult(temp2));
	
	return c;
}