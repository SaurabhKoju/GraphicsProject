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

float Camera::speed = 6;

void Camera::ZoomIn(float time) {
	Vec4 v = scale((this->look), {speed * time, speed * time, speed * time});
	position = position + v;
	Camera::update(this->position, this->target);
}
void Camera::ZoomOut(float time) {
	Vec4 v = scale((this->look), {speed * time, speed * time, speed * time});
	position = position - v;
	Camera::update(this->position, this->target);
}

void Camera::moveUp(float time) {
	Vec4 v = scale(this->down, {speed * time, speed * time, speed * time});
	position = position - v;
	Camera::update(this->position, this->target);
}
void Camera::moveDown(float time) {
	Vec4 v = scale(this->down, {speed * time, speed * time, speed * time});
	position = position + v;
	Camera::update(this->position, this->target);
}
void Camera::rotateLeft(float time) {
	Vec4 v = scale(this->right, {speed * time, speed * time, speed * time});
	position = position - v;
	Camera::update(this->position, this->target);
}
void Camera::rotateRight(float time) {
	Vec4 v = scale(this->right, {speed * time, speed * time, speed * time});
	position = position + v;
	Camera::update(this->position, this->target);
}


void Camera::moveLeft(float time) {
	Vec4 v = scale(this->right, { speed * time, speed * time, speed * time });
	position = position - v;
	target = target - v;
	Camera::update(this->position, this->target);
}

void Camera::moveRight(float time) {
	Vec4 v = scale(this->right, { speed * time, speed * time, speed * time });
	position = position + v;
	target = target + v;
	Camera::update(this->position, this->target);
}

Mat4 worldtoCam(Camera cam) {
	Mat4 ans = getTransformMatrix(cam.right, cam.down, cam.look);
	return(transpose(ans));
}

Mat4 camtoWorld(Camera cam) {
	return(getTransformMatrix(cam.right, cam.down, cam.look));
}

Mat4 screentoWindow(Camera cam){
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