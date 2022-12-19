#pragma once

#include "Extern.h"
#include "Define.h"

class Camera;

class Math {
public:
	static Eigen::Matrix4f getScale(float sx, float sy, float sz);
	static Eigen::Matrix4f getScale(float s);
	static Eigen::Matrix4f getTranslation(float tx, float ty, float tz);
	static Eigen::Matrix4f getTranslation(Eigen::Vector3f t);
	static Eigen::Matrix4f getRotateX(Radian theta);
	static Eigen::Matrix4f getRotateY(Radian theta);
	static Eigen::Matrix4f getRotateZ(Radian theta);
	static Eigen::Matrix4f getView(Eigen::Vector3f pos, Eigen::Vector3f lookAt, Eigen::Vector3f up);
	static Eigen::Matrix4f getProj(float n, float f, Radian fov, float aspect);
	static Eigen::Matrix4f getOrtho(float l, float r, float b, float t, float n, float f);
private:
	static Eigen::Vector4f makeVec(float x, float y, float z);
	static Eigen::Vector3f makeVec3d(float x, float y, float z);
	static Eigen::Vector3f getUpVector(Radian pitch, Radian yaw);
	static Radian getPitch(Eigen::Vector3f lookAt);
	static Radian getYaw(Eigen::Vector3f lookAt);
	static Eigen::Vector3f getUpVector(Eigen::Vector3f lookAt);
};

