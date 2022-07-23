#pragma once
#include "GMath.h"

class Camera {
public:
	Vec3 position;
	Vec3 target;

	Vec3 down;
	Vec3 right;
	Vec3 look;

	static float speed;

	void update(Vector<3> cameraPosition, Vector<3> targetPosition);

	void ZoomIn(float time);
	void ZoomOut(float time);
	void moveUp(float time);
	void moveDown(float time);
	void moveRight(float time);
	void moveLeft(float time);
};

Mat4 rotateCam(Camera cam);
