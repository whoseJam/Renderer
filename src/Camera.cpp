
#include <iostream>

#include "Extern.h"
#include "Camera.h"
#include "Define.h"
#include "Input.h"
#include "Math.h"
#include "Object.h"
#include "UI.h"

using namespace Eigen;
using namespace std;

void Camera::showUI() {
    UI::text("<Camera>");
    UI::text("pitch=%.2lf yaw=%.2lf", pitch, yaw);
    UI::inputFloat("fov", &fov);
}

void Camera::initCamera(int left, int bottom, int width, int height, Degree yaw, Degree pitch, float far, float near, float fov) {
    this->left = left;
    this->buttom = bottom;
    this->width = width;
    this->height = height;
    this->aspect = 4.0 / 3.0;
    this->near = near;
    this->far = far;
    this->fov = fov;
    this->yaw = yaw;
    this->pitch = min(89.0f, max(-89.0f, pitch));
    updateUpAndLookAt(this->pitch, this->yaw);
}

Camera::Camera(Object* parent, int width, int height) :
    Component(Component::Type::Camera, parent) {
    initCamera(0, 0, width, height, -90, 0, 1000.0f, 0.01f, 60);
}

Camera::Camera(Object* parent, int left, int buttom, int width, int height) :
    Component(Component::Type::Camera, parent) {
    initCamera(left, buttom, width, height,  -90, 0, 1000.0f, 0.01f, 60);
}

int Camera::getButtom() const {
    return buttom;
}

int Camera::getLeft() const {
    return left;
}

int Camera::getWidth() const {
    return width;
}

int Camera::getHeight() const {
    return height;
}

WPos Camera::getLookAt() const {
    return lookAt;
}

float Camera::getNear() const {
    return near;
}

float Camera::getFar() const {
    return far;
}

Degree Camera::getFOV() const {
    return fov;
}

string Camera::toString() const {
    return "Camera";
}

float Camera::getNearScreenLeft() const {
    float PI = acos(-1);
    float t = near * tan(fov * PI / 180 / 2);
    float r = aspect * t;
    return -r;
}

float Camera::getNearScreenRight() const {
    float PI = acos(-1);
    float t = near * tan(fov * PI / 180 / 2);
    float r = aspect * t;
    return r;
}

float Camera::getNearScreenButtom() const {
    float PI = acos(-1);
    float t = near * tan(fov * PI / 180 / 2);
    return -t;
}

float Camera::getNearScreenTop() const {
    float PI = acos(-1);
    float t = near * tan(fov * PI / 180 / 2);
    return t;
}

void Camera::updateUpAndLookAt(Degree pitch, Degree yaw) {
    float PI = (float)acos(-1);
    Radian Y = yaw * PI / 180;
    Radian P = pitch * PI / 180;
    this->lookAt = WPos(cos(Y) * cos(P), sin(P), sin(Y) * cos(P)).normalized();
    this->up = WPos(-sin(P) * cos(Y), cos(P), -sin(P) * sin(Y)).normalized();
}

Matrix4f Camera::getView() const {
    return Math::getView(
        getParent()->getPosition(),
        lookAt, up);
}

Matrix4f Camera::getPerspective() const {
    float PI = (float)acos(-1);
    return Math::getProj(near, far, fov * PI / 180, aspect);
}

Matrix4f Camera::getOrthogonal() const {
    return Math::getOrtho(-10, 10, -10, 10, near, far);
}

void Camera::setUnityControl() {
    Input::onScroll([&](double xoffset, double yoffset) {
        float cameraSpeed = 0.2 * yoffset;
        WPos pos = getParent()->getPosition();
        pos += cameraSpeed * lookAt;
        getParent()->setPosition(pos);
    });
    struct MouseMoveCallback {
        bool firstMouse;
        float lastX;
        float lastY;
        Camera* camera;
        MouseMoveCallback(Camera* camera) {
            firstMouse = true;
            lastX = lastY = 0;
            this->camera = camera;
        }
        void operator()(double xposIn, double yposIn) {
            float xpos = (float)xposIn;
            float ypos = (float)yposIn;
            if (firstMouse) {
                lastX = xpos;
                lastY = ypos;
                firstMouse = false;
            }
            float xoffset = xpos - lastX;
            float yoffset = lastY - ypos;
            lastX = xpos;
            lastY = ypos;
            if (Input::getMouseRightDown()) {
                float sensitivity = 0.1f;
                camera->yaw += xoffset * sensitivity;
                camera->pitch += yoffset * sensitivity;
                camera->pitch = min(89.0f, max(-89.0f, camera->pitch));
                camera->updateUpAndLookAt(camera->pitch, camera->yaw);
            }
            if (Input::getMouseMiddleDown()) {
                float sensitivity = 0.01f;
                WPos pos = camera->getParent()->getPosition();
                WPos up = camera->up;
                WPos lookAt = camera->lookAt;
                WPos right = lookAt.cross(up).normalized();
                pos = pos - (up * yoffset + right * xoffset) * sensitivity;
                camera->getParent()->setPosition(pos);
            }
        }
    };
    Input::onMouseMove(MouseMoveCallback(this));
}

void Camera::setFPSControl() {
    Input::fixMouseAtScreenCenter();
    Input::onButtonDown([&](double delta) {
        float cameraSpeed = 2.0 * delta;
        WPos pos = getParent()->getPosition();
        pos += cameraSpeed * lookAt;
        getParent()->setPosition(pos);
    }, GLFW_KEY_W);
    Input::onButtonDown([&](double delta) {
        float cameraSpeed = 2.0 * delta;
        WPos pos = getParent()->getPosition();
        pos -= cameraSpeed * lookAt;
        getParent()->setPosition(pos);
    }, GLFW_KEY_S);
    Input::onButtonDown([&](double delta) {
        float cameraSpeed = 2.0 * delta;
        WPos pos = getParent()->getPosition();
        pos -= cameraSpeed * lookAt.cross(up).normalized();
        getParent()->setPosition(pos);
    }, GLFW_KEY_A);
    Input::onButtonDown([&](double delta) {
        float cameraSpeed = 2.0 * delta;
        WPos pos = getParent()->getPosition();
        pos += cameraSpeed * lookAt.cross(up).normalized();
        getParent()->setPosition(pos);
    }, GLFW_KEY_D);
    
    struct MouseMoveCallback {
        bool firstMouse;
        float lastX;
        float lastY;
        Camera* camera;
        MouseMoveCallback(Camera* camera) {
            firstMouse = true;
            lastX = lastY = 0;
            this->camera = camera;
        }
        void operator()(double xposIn, double yposIn) {
            float xpos = (float)xposIn;
            float ypos = (float)yposIn;
            if (firstMouse) {
                lastX = xpos;
                lastY = ypos;
                firstMouse = false;
            }
            float xoffset = xpos - lastX;
            float yoffset = lastY - ypos;
            lastX = xpos;
            lastY = ypos;
            float sensitivity = 0.1f;
            xoffset *= sensitivity;
            yoffset *= sensitivity;
            camera->yaw += xoffset;
            camera->pitch += yoffset;
            camera->pitch = min(89.0f, max(-89.0f, camera->pitch));
            camera->updateUpAndLookAt(camera->pitch, camera->yaw);
        }
    };
    Input::onMouseMove(MouseMoveCallback(this));

    Input::onButtonDown([&](double delta) {
        Input::closeWindow();
    }, GLFW_KEY_Q);
}