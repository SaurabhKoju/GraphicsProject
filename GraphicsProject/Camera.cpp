#include "Camera.h"
#include "GMath.h"
#include "Primitives.h"
#include "Projection.h"

void Camera::update(Vec4 cameraPosition, Vec4 targetPosition) {
	position = cameraPosition;
	target = targetPosition;
	look = normalize(targetPosition - cameraPosition);
	right = normalize(look * Vec4{0, 0, 1});
	down = look * right;
}

float Camera::speed = 4;

void Camera::ZoomIn(float time) {
	Vec4 v = scale(normalize(this->look), {speed * time, speed * time, speed * time});
	position = position + v;
	Camera::update(this->position, this->target);
}
void Camera::ZoomOut(float time) {
	Vec4 v = scale(normalize(this->look), {speed * time, speed * time, speed * time});
	position = position - v;
	Camera::update(this->position, this->target);

}

void Camera::moveUp(float time) {
	Vec4 base = this->look * this->right;
	Vec4 v = scale(normalize(base), {speed * time, speed * time, speed * time});
	position = position - v;
	Camera::update(this->position, this->target);
}
void Camera::moveDown(float time) {
	Vec4 base = this->look * this->right;
	Vec4 v = scale(normalize(base), {speed * time, speed * time, speed * time});
	position = position + v;
	Camera::update(this->position, this->target);
}
void Camera::moveLeft(float time) {
	Vec4 base = this->look * this->down;
	Vec4 v = scale(normalize(base), {speed * time, speed * time, speed * time});
	position = position + v;
	Camera::update(this->position, this->target);
}
void Camera::moveRight(float time) {
	Vec4 base = this->look * this->down;
	Vec4 v = scale(normalize(base), {speed * time, speed * time, speed * time});
	position = position - v;
	Camera::update(this->position, this->target);
}

Mat4 worldtoCam(Camera cam) {
	Mat3 rotate = inverse(getTransformMatrix(cam.right, cam.down, cam.look));
	Mat4 ans = {
		rotate.matrix[0][0], rotate.matrix[0][1], rotate.matrix[0][2], 0,
		rotate.matrix[1][0], rotate.matrix[1][1], rotate.matrix[1][2], 0,
		rotate.matrix[2][0], rotate.matrix[2][1], rotate.matrix[2][2], 0,
		0, 0, 0, 1
	};
	return ans;
}

Mat4 camtoWorld(Camera cam) {
	Mat3 rotate = getTransformMatrix(cam.right, cam.down, cam.look);
	Mat4 ans = {
		rotate.matrix[0][0], rotate.matrix[0][1], rotate.matrix[0][2], 0,
		rotate.matrix[1][0], rotate.matrix[1][1], rotate.matrix[1][2], 0,
		rotate.matrix[2][0], rotate.matrix[2][1], rotate.matrix[2][2], 0,
		0, 0, 0, 1
	};
	return ans;
}

Mat4 screentoPort(Camera cam){
	Mat4 expandx = getScaleMatrix(Vec4{ 1 / aspect_ratio, 1, 1, 1 });
	Mat4 translateCam = getTranslateMatrix(cam.position);
	Mat4 PortCam = expandx * getTranslateMatrix({ -1, -1, 0 }) * getScaleMatrix({ float(2) / SCREEN_WIDTH, float(2) / SCREEN_HEIGHT, 1 });
	Mat4 ans = translateCam * camtoWorld(cam) * PortCam;
	return ans;
}

Vec4 worldtoScreen(Camera cam, Vec4 x) {
	Mat4 compressx = getScaleMatrix(Vec4{ aspect_ratio, 1, 1 });
	Mat4 translateCam = getTranslateMatrix(Zero4 - cam.position);
	Mat4 camTransform = worldtoCam(cam);
	Mat4 Transform = compressx * camTransform * translateCam;
	x = get2d(Transform * x);
	Mat4 maptoScreen = getScaleMatrix({ SCREEN_WIDTH / float(2), SCREEN_HEIGHT / float(2), 1 }) * getTranslateMatrix({ 1, 1, 0 });
	x = maptoScreen * x;
	return x;
}