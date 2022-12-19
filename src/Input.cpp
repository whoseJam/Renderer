
#include <functional>
#include <vector>
#include <utility>
#include <mutex>
#include <map>

#include "Extern.h"
#include "Window.h"
#include "IDGenerator.h"
#include "Define.h"
#include "Input.h"

using namespace std;

namespace {
    bool mouseLeftDown;
    bool mouseRightDown;
    bool mouseMiddleDown;
    vector<pair<FuncID, OnScrollFunc>> scrollCallbacks;
    vector<pair<FuncID, OnMouseMoveFunc>> mouseMoveCallbacks;
    map<int,
        vector<pair<FuncID, OnButtonDownFunc>>
    > buttonDownCallbacks;
    vector<pair<FuncID, OnMouseDownFunc>> mouseLeftDownCallbacks;
    vector<pair<FuncID, OnMouseDownFunc>> mouseRightDownCallbacks;
    vector<pair<FuncID, OnMouseDownFunc>> mouseMiddleDownCallbacks;

    void GLFWOnScrollCallback(GLFWwindow* window, double width, double height) {
        ImGui_ImplGlfw_ScrollCallback(window, width, height);
        for (const auto& scrollFunc : scrollCallbacks) {
            scrollFunc.second(width, height);
        }
    }

    void GLFWOnMouseMoveCallback(GLFWwindow* window, double width, double height) {
        ImGui_ImplGlfw_CursorPosCallback(window, width, height);
        for (const auto& mouseMoveFunc : mouseMoveCallbacks) {
            mouseMoveFunc.second(width, height);
        }
    }

    void GLFWOnMouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
        ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods);
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) != GLFW_RELEASE) {
            mouseLeftDown = true;
            for (const auto& mouseDownFunc : mouseLeftDownCallbacks) {
                mouseDownFunc.second();
            }
        }
        else mouseLeftDown = false;

        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) != GLFW_RELEASE) {
            mouseRightDown = true;
            for (const auto& mouseDownFunc : mouseRightDownCallbacks) {
                mouseDownFunc.second();
            }
        }
        else mouseRightDown = false;

        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) != GLFW_RELEASE) {
            mouseMiddleDown = true;
            for (const auto& mouseDownFunc : mouseMiddleDownCallbacks) {
                mouseDownFunc.second();
            }
        }
        else mouseMiddleDown = false;
    }
}

namespace Input {
    void initialize() {
        //ImGui_ImplGlfw_WindowFocusCallback(GLFWwindow * window, int focused);        // Since 1.84
        //ImGui_ImplGlfw_CursorEnterCallback(GLFWwindow * window, int entered);        // Since 1.84
        //ImGui_ImplGlfw_CursorPosCallback(GLFWwindow * window, double x, double y);   // Since 1.87
        //ImGui_ImplGlfw_MouseButtonCallback(GLFWwindow * window, int button, int action, int mods);
        //ImGui_ImplGlfw_ScrollCallback(GLFWwindow * window, double xoffset, double yoffset);
        //ImGui_ImplGlfw_KeyCallback(GLFWwindow * window, int key, int scancode, int action, int mods);
        //ImGui_ImplGlfw_CharCallback(GLFWwindow * window, unsigned int c);
        //ImGui_ImplGlfw_MonitorCallback(GLFWmonitor * monitor, int event);
        glfwSetScrollCallback(Window::getWindow(), GLFWOnScrollCallback);
        glfwSetCursorPosCallback(Window::getWindow(), GLFWOnMouseMoveCallback);
        glfwSetMouseButtonCallback(Window::getWindow(), GLFWOnMouseButtonCallback);
    }

    FuncID onScroll(OnScrollFunc callback) {
        FuncID funcId = IDGenerator::getFuncID();
        scrollCallbacks.push_back(make_pair(funcId, callback));
        return funcId;
    }

    FuncID onMouseMove(OnMouseMoveFunc callback) {
        FuncID funcId = IDGenerator::getFuncID();
        mouseMoveCallbacks.push_back(make_pair(funcId, callback));
        return funcId;
    }

    FuncID onButtonDown(OnButtonDownFunc callback, int key) {
        FuncID funcId = IDGenerator::getFuncID();
        auto it = buttonDownCallbacks.find(key);
        if (it == buttonDownCallbacks.end()) {
            buttonDownCallbacks.insert({
                key,
                vector<pair<FuncID, OnButtonDownFunc>>{
                    make_pair(funcId, callback)
                }
                });
        }
        else {
            it->second.push_back(make_pair(funcId, callback));
        }
        return funcId;
    }

    FuncID onMouseDown(OnMouseDownFunc callback, Mouse key) {
        FuncID funcId = IDGenerator::getFuncID();
        switch (key) {
        case Mouse::Left:
            mouseLeftDownCallbacks.push_back(make_pair(funcId, callback));
            break;
        case Mouse::Middle:
            mouseMiddleDownCallbacks.push_back(make_pair(funcId, callback));
            break;
        case Mouse::Right:
            mouseRightDownCallbacks.push_back(make_pair(funcId, callback));
            break;
        }
        return funcId;
    }

    void update() {
        static float lastTime = 0;
        float nowTime = glfwGetTime();
        float deltaTime = nowTime - lastTime;
        lastTime = nowTime;
        for (int i = 'A'; i <= 'Z'; i++) {
            if (glfwGetKey(Window::getWindow(), i)) {
                auto it = buttonDownCallbacks.find(i);
                if (it == buttonDownCallbacks.end()) {
                }
                else {
                    for (const auto& buttonDownFunc : it->second) {
                        buttonDownFunc.second(deltaTime);
                    }
                }
            }
        }
        glfwSwapBuffers(Window::getWindow());
        glfwPollEvents();
    }

    void fixMouseAtScreenCenter() {
        glfwSetInputMode(Window::getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    void closeWindow() {
        glfwSetWindowShouldClose(Window::getWindow(), true);
        exit(0);    //TODO
    }

    bool getMouseLeftDown() {
        return mouseLeftDown;
    }

    bool getMouseRightDown() {
        return mouseRightDown;
    }

    bool getMouseMiddleDown() {
        return mouseMiddleDown;
    }

    bool getMouseDown(Mouse key) {
        switch (key) {
        case Mouse::Left:
            return mouseLeftDown;
        case Mouse::Right:
            return mouseRightDown;
        case Mouse::Middle:
            return mouseMiddleDown;
        }
    }
}