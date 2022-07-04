#include "Camera.h"
#include "GMath.h"

void Camera::update(Vector<3> cameraPosition, Vector<3> targetPosition) {
	position = cameraPosition;
	look = normalize(targetPosition - cameraPosition);
	right = normalize(look * Vector<3>{0, 0, 1});
	down = look * right;

}

Mat4 rotateCam(Camera cam) {
	Mat3 rotate = inverse(getTransformMatrix(cam.right, cam.down, cam.look));
	Mat4 ans = {
		rotate.matrix[0][0], rotate.matrix[0][1], rotate.matrix[0][2], 0,
		rotate.matrix[1][0], rotate.matrix[1][1], rotate.matrix[1][2], 0,
		rotate.matrix[2][0], rotate.matrix[2][1], rotate.matrix[2][2], 0,
		0, 0, 0, 1
	};
	return ans;
}


