#pragma once

#include <vector>
#include <string>
#include "Extern.h"
#include "Define.h"

class Object;
class Scene;
class Resource;

namespace UI {
    void initialize();
    void render();
    void update();
    void destroy();


    void whichObjectDisplayComponent(Object* target);
    void whichSceneDisplayHierarchy(Scene* target);
    void whichResourceDisplay(Resource* target);


    bool isItemClicked();


    template<typename ...Args>
    void text(const std::string& fmt, Args ...args) {
        ImGui::Text(fmt.c_str(), args...);
    }
    template<typename ...Args>
    void textColored(Color color, const std::string& fmt, Args ...args) {
        float r = color(0);
        float g = color(1);
        float b = color(2);
        ImGui::TextColored(ImColor(r, g, b, 1.0), fmt.c_str(), args...);
    }
    template<typename ...Args>
    void textWrapped(const std::string& fmt, Args ...args) {
        ImGui::TextWrapped(fmt.c_str(), args...);
    }
    template<typename ...Args>
    void bulletText(const std::string& fmt, Args ...args) {
        ImGui::BulletText(fmt.c_str(), args...);
    }
    void bullet();
    bool button(const std::string& msg);
    bool invisibleButton();
    void sliderFloat(const std::string& msg, float* value, float l, float r);
    void sliderFloat2(const std::string& msg, float* value, float l, float r);
    void sliderFloat3(const std::string& msg, float* value, float l, float r);
    void sliderWPos(const std::string& msg, WPos* value, float l, float r);
    void checkBox(bool* addr);
    void checkBox(const std::string& msg, bool* addr);
    void sameLine();
    void combo(const std::string& msg, const std::vector<std::string>& items, int* selected);
    void inputColor(const std::string& msg, Color* color);
    void inputFloat(const std::string& msg, float* addr);
    void inputFloat2(const std::string& msg, float* addr);
    void inputFloat3(const std::string& msg, float* addr);
    void inputWPos(const std::string& msg, WPos& pos);
    void inputWPos(const std::string& msg, WPos* pos);
    void beginTabBar(const std::string& msg);
    void tabItemButton(const std::string& msg);
    void endTabBar();
    void begin(const std::string& msg);
    void end();
};
/*
initialize
for-loop:
    update
        <ui set>
    render
destroy
*/
