#pragma once
#include "GMath.h"

class Camera {
public:
	Vector<3> position;
	Vector<3> down;
	Vector<3> right;
	Vector<3> look;

	void update(Vector<3> cameraPosition, Vector<3> targetPosition);
};

Mat4 rotateCam(Camera cam);
