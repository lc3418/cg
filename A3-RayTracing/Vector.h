#ifndef _VECTOR_H_
#define _VECTOR_H_


class Vector {
public:
	float x;
	float y;
	float z;

	Vector();
	Vector(float x, float y, float z);
	~Vector();

	float dot(Vector a); //dot product
	Vector cross(Vector a); //cross product
	Vector normal(); //normalize the vector
	float distance(Vector a); //get the distance

	bool operator ==  (const Vector v) {
		return (x == v.x && y == v.y && z == v.z);
	}
};


#endif


