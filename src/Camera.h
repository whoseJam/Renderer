#pragma once

#include "Define.h"
#include "Component.h"

class Math;

class Camera : public Component {
public:
    Camera(Object* parent, int width, int height);
    Camera(Object* parent, int x, int y, int width, int height);
    
    void setFPSControl();
    void setUnityControl();

    int getButtom() const;
    int getLeft() const;
    int getWidth() const;
    int getHeight() const;
    WPos getLookAt() const;

    float getNear() const;
    float getFar() const;
    Degree getFOV() const;
    float getNearScreenLeft() const;
    float getNearScreenRight() const;
    float getNearScreenTop() const;
    float getNearScreenButtom() const;

    Eigen::Matrix4f getView() const;
    Eigen::Matrix4f getPerspective() const;
    Eigen::Matrix4f getOrthogonal() const;

    virtual std::string toString() const override;
    virtual void showUI() override;
private:
    int buttom;
    int left;
    int width;
    int height;
    float aspect;
    float near;
    float far;
    Degree fov;
    Degree yaw;
    Degree pitch;
    WPos lookAt;
    WPos up;

    void initCamera(int left, int buttom, int width, int height, Degree yaw, Degree pitch, float far, float near, Degree fov);
    void updateUpAndLookAt(float pitch, float yaw);
};

