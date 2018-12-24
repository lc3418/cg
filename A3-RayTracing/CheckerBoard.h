#ifndef _CHECKERBOARD_H_
#define _CHECKERBOARD_H_
#include "Color.h"
#include "Vector.h"
#include "Ray.h"
#include <stdlib.h>

class CheckerBoard{
private:
	float size;
	
public:
	CheckerBoard();
	~CheckerBoard();
	CheckerBoard(float size);
	virtual Color sample(Ray r, Vector v, Vector n);

};

#endif 

