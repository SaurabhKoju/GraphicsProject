#include "Camera.h"
#include "GMath.h"

void Camera::update(Vec3 cameraPosition, Vec3 targetPosition) {
	position = cameraPosition;
	target = targetPosition;
	look = normalize(targetPosition - cameraPosition);
	right = normalize(look * Vector<3>{0, 0, 1});
	down = look * right;
}

float Camera::speed = 2;

void Camera::ZoomIn(float time) {
	Vec3 v = scale(normalize(this->look), {speed * time, speed * time, speed * time});
	position = position + v;
	Camera::update(this->position, this->target);
}
void Camera::ZoomOut(float time) {
	Vec3 v = scale(normalize(this->look), {speed * time, speed * time, speed * time});
	position = position - v;
	Camera::update(this->position, this->target);

}

void Camera::moveUp(float time) {
	Vec3 base = this->look * this->right;
	Vec3 v = scale(normalize(base), {speed * time, speed * time, speed * time});
	position = position - v;
	Camera::update(this->position, this->target);
}
void Camera::moveDown(float time) {
	Vec3 base = this->look * this->right;
	Vec3 v = scale(normalize(base), {speed * time, speed * time, speed * time});
	position = position + v;
	Camera::update(this->position, this->target);
}
void Camera::moveLeft(float time) {
	Vec3 base = this->look * this->down;
	Vec3 v = scale(normalize(base), {speed * time, speed * time, speed * time});
	position = position + v;
	Camera::update(this->position, this->target);
}
void Camera::moveRight(float time) {
	Vec3 base = this->look * this->down;
	Vec3 v = scale(normalize(base), {speed * time, speed * time, speed * time});
	position = position - v;
	Camera::update(this->position, this->target);
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
