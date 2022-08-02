#pragma once
#include "GMath.h"

class Camera {
public:
	Vec4 position;
	Vec4 target;

	Vec4 down;
	Vec4 right;
	Vec4 look;

	static float speed;

	void update(Vec4 cameraPosition, Vec4 targetPosition);

	void ZoomIn(float time);
	void ZoomOut(float time);
	void moveUp(float time);
	void moveDown(float time);
	void moveRight(float time);
	void moveLeft(float time);
	void rotateLeft(float time);
	void rotateRight(float time);
};

Mat4 worldtoCam(Camera cam);
Mat4 camtoWorld(Camera cam);
Mat4 screentoPort(Camera cam);
Vec4 worldtoScreen(Camera cam, Vec4 x);