

#include "Window.h"
#include "Extern.h"
#include "Logger.h"
#include "Scene.h"
#include "Object.h"
#include "Resource.h"
#include "UI.h"

using namespace std;

namespace UI {
    //  state machine
    Object* objectDisplayComponent = nullptr;
    Scene* sceneDisplayHierarchy = nullptr;
    Resource* resouceDisplay = nullptr;
    void whichObjectDisplayComponent(Object* target) {
        objectDisplayComponent = target;
    }
    void whichSceneDisplayHierarchy(Scene* target) {
        sceneDisplayHierarchy = target;
    }
    void whichResourceDisplay(Resource* target) {
        resouceDisplay = target;
    }

    // code flow
    void initialize() {
        if (!glfwInit()) 
            Logger::error("glfw Failed to Initialize (UI.cpp)");
        const char* glsl_version = "#version 130";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        Window::initialize();
        GLFWwindow* window = Window::getWindow();
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsLight();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init(glsl_version);
        io.Fonts->AddFontFromFileTTF("font/Consolas.ttf", 25.0f);
    }

    void update() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        if (sceneDisplayHierarchy != nullptr) 
            sceneDisplayHierarchy->showHierarchyUI();
        if (objectDisplayComponent != nullptr) 
            objectDisplayComponent->showComponentUI();
        if (resouceDisplay != nullptr)
            resouceDisplay->showUI();
    }

    void render() {
        ImGui::Render();
        int width, height;
        glfwGetFramebufferSize(Window::getWindow(), &width, &height);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void destroy() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

//  event listener
    bool isItemClicked() {
        return ImGui::IsItemClicked();
    }

//  UI items
    void sliderFloat(const string& msg, float* value, float l, float r) {
        ImGui::SliderFloat(msg.c_str(), value, l, r);
    }

    void sliderFloat2(const string& msg, float *value, float l, float r) {
        ImGui::SliderFloat2(msg.c_str(), value, l, r);
    }

    void sliderFloat3(const string& msg, float* value, float l, float r) {
        ImGui::SliderFloat3(msg.c_str(), value, l, r);
    }

    void sliderWPos(const string& msg, WPos* wpos, float l, float r) {
        sliderFloat3(msg, (float*)wpos, l, r);
    }

    void checkBox(bool* addr) {
        ImGui::Checkbox(" ", addr);
    }

    void checkBox(const string& msg, bool* addr) {
        if (msg.length() == 0)
            ImGui::Checkbox(" ", addr);
        else
            ImGui::Checkbox(msg.c_str(), addr);
    }

    void combo(const std::string& msg, const vector<string>& items, int* selected) {
        string ans;
        int tot = 0;
        int len = 1;
        for (const string& str : items)
            len += str.length() + 1;
        char* buffer = new char[len];
        memset(buffer, 0, sizeof(char) * len);
        for (const string& str : items) {
            for (int i = 0; i < str.length(); i++)
                buffer[tot++] = str[i];
            buffer[tot++] = '\0';
        }
        ImGui::Combo(msg.c_str(), selected, buffer, items.size());
        delete[] buffer;
    }

    void inputColor(const std::string& msg, float* addr) {
        ImGui::ColorEdit3(msg.c_str(), addr);
    }

    void inputColor(const std::string& msg, Color* color) {
        ImGui::ColorEdit3(msg.c_str(), (float*)color);
    }

    void inputFloat(const std::string& msg, float* addr) {
        ImGui::InputFloat(msg.c_str(), addr);
    }

    void inputFloat2(const std::string& msg, float* addr) {
        ImGui::InputFloat2(msg.c_str(), addr);
    }

    void inputFloat3(const std::string& msg, float* addr) {
        ImGui::InputFloat3(msg.c_str(), addr);
    }

    void inputWPos(const std::string& msg, WPos& value) {
        inputFloat3(msg, (float*)&value);
    }

    void inputWPos(const std::string& msg, WPos* addr) {
        inputFloat3(msg, (float*)addr);
    }

    void sameLine() {
        ImGui::SameLine();
    }

    void bullet() {
        ImGui::Bullet();
    }

    bool button(const std::string& msg) {
        return ImGui::Button(msg.c_str());
    }
    
    bool invisibleButton() {
        return ImGui::InvisibleButton("InvisibleButton", ImVec2(50, 50));
    }

    void beginTabBar(const std::string& msg) {
        ImGui::BeginTabBar(msg.c_str());
    }

    void tabItemButton(const std::string& msg) {
        ImGui::TabItemButton(msg.c_str());
    }

    void endTabBar() {
        ImGui::EndTabBar();
    }

    void begin(const std::string& title) {
        ImGui::Begin(title.c_str());
    }

    void end() {
        ImGui::End();
    }
}