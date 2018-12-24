#ifndef _CONTROLPOINT_H_
#define _CONTROLPOINT_H_

class ControlPoint {
public:
	float x;
	float y;

	ControlPoint();
	~ControlPoint();
	ControlPoint(float x, float y);

	bool operator == (const ControlPoint c) {
		return (x == c.x && y == c.y);
	}
};

#endif
