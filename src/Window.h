#pragma once

#include <string>

#include "Extern.h"

namespace Window {
    void initialize();
    void setWidth(int width);
    void setHeight(int height);
    void setTitle(const std::string& title);
    GLFWwindow* getWindow();
    void destroy();
};
