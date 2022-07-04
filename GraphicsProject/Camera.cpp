#include "Camera.h"
#include "GMath.h"

void Camera::updateCamera(Vector<3> cameraPosition, Vector<3> targetPosition) {
	position = cameraPosition;
	look = normalize(targetPosition - cameraPosition);
	right = normalize(look * Vector<3>{0, 0, 1});
	down = look * right;
}


