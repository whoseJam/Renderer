#pragma once

#include <functional>
#include <vector>
#include "Define.h"

namespace Input {
    enum class Mouse {
        Left,
        Right,
        Middle
    };

    void initialize();

    FuncID onScroll(OnScrollFunc callback);
    FuncID onMouseMove(OnMouseMoveFunc callback);
    FuncID onMouseDown(OnMouseDownFunc callback, Mouse key);
    FuncID onButtonDown(OnButtonDownFunc callback, int key);
    bool getMouseLeftDown();
    bool getMouseRightDown();
    bool getMouseMiddleDown();
    bool getMouseDown(Mouse key);
    void update();
    void fixMouseAtScreenCenter();
    void closeWindow();
};
