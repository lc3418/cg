#include "Union.h"

Union::Union() {};
Union::~Union() {};

Union::Union(Plane p, Sphere s) {
	this->p = p;
	this->s = s;
}

Intersect Union::intersect(Ray r) {
	Intersect i = Intersect();
	if (p.intersect(r).intersected == false && s.intersect(r).intersected == false) {
		return i;
	}
	else if (p.intersect(r).intersected == true && s.intersect(r).intersected == false) {
		return p.intersect(r);
	}
	else if (p.intersect(r).intersected == false && s.intersect(r).intersected == true) {
		return s.intersect(r);
	}
	else if (p.intersect(r).intersected == true && s.intersect(r).intersected == true) {
		if (p.intersect(r).distance < s.intersect(r).distance) {
			return p.intersect(r);
		}
		else {
			return s.intersect(r);
		}
	}
	return i;
}