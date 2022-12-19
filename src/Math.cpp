
#include "Math.h"
#include "Camera.h"

using namespace std;
using namespace Eigen;

Vector3f Math::getUpVector(Radian pitch, Radian yaw) {
	Radian Y = yaw;
	Radian P = pitch;
	return WPos(-sin(P) * cos(Y), cos(P), -sin(P) * sin(Y)).normalized();
}

Radian Math::getPitch(Vector3f lookAt) {
	float PI = acos(-1);
	float x = lookAt(0);
	float z = lookAt(2);
	float r = sqrt(x * x + z * z);
	float y = lookAt(1);
	float tanValue = y / r;
	return atan(tanValue);
}

Radian Math::getYaw(Vector3f lookAt) {
	float PI = acos(-1);
	float x = lookAt(0);
	float z = lookAt(2);
	return atan2(z, x);
}

Vector3f Math::getUpVector(Vector3f lookAt) {
	return getUpVector(getPitch(lookAt), getYaw(lookAt));
}

Matrix4f Math::getScale(float sx, float sy, float sz) {
	Eigen::Matrix4f tmp(4, 4);
	tmp <<
		sx, 0, 0, 0,
		0, sy, 0, 0,
		0, 0, sz, 0,
		0, 0, 0, 1;
	return tmp;
}

Matrix4f Math::getScale(float s) {
	return getScale(s, s, s);
}

Matrix4f Math::getTranslation(float tx, float ty, float tz) {
	Matrix4f tmp(4, 4);
	tmp <<
		1, 0, 0, tx,
		0, 1, 0, ty,
		0, 0, 1, tz,
		0, 0, 0, 1;
	return tmp;
}

Matrix4f Math::getTranslation(Vector3f t) {
	return getTranslation(t(0), t(1), t(2));
}

Matrix4f Math::getView(Vector3f pos, Vector3f lookat, Vector3f up) {
	Vector3f& e = pos;
	Vector3f& g = lookat;
	Vector3f& t = up;
	Vector3f tmp = g.cross(t);
	Matrix4f viewInv(4, 4);
	viewInv <<
		tmp(0), t(0), g(0), 0,
		tmp(1), t(1), g(1), 0,
		tmp(2), t(2), g(2), 0,
		0, 0, 0, 1;
	return viewInv.transpose() * getTranslation(-e(0), -e(1), -e(2));
}

Matrix4f Math::getProj(float n, float f, float fov, float aspect) {
	Matrix4f proj(4, 4);
	float t = n * tan(fov / 2);
	float r = aspect * t;
	proj <<
		n / r, 0, 0, 0,
		0, n / t, 0, 0,
		0, 0, -(n + f) / (n - f), 2 * n * f / (n - f),
		0, 0, 1, 0;
	return proj;
}

Matrix4f Math::getOrtho(float l, float r, float b, float t, float n, float f) {
	float mid_lr = (l + r) / 2, len_lr = r - l;
	float mid_tb = (t + b) / 2, len_tb = t - b;
	float mid_fn = (n + f) / 2, len_fn = f - n;
	Vector4f at(0, 0, 5, 1);
	return getScale(2 / len_lr, 2 / len_tb, 2 / len_fn) * getTranslation(-mid_lr, -mid_tb, -mid_fn);
}

Vector4f Math::makeVec(float x, float y, float z) {
	Vector4f ans(x, y, z, 1.0);
	return ans;
}

Vector3f Math::makeVec3d(float x, float y, float z) {
	Vector3f ans(x, y, z);
	return ans;
}

Matrix4f Math::getRotateX(float theta) {
	Matrix4f tmp(4, 4);
	tmp <<
		1, 0, 0, 0,
		0, sin(theta), -cos(theta), 0,
		0, cos(theta), sin(theta), 0,
		0, 0, 0, 1;
	return tmp;
}