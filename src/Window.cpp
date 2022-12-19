
#include "Extern.h"
#include "Window.h"
#include "Logger.h"

using namespace std;

namespace Window {
	bool inited = false;
	int width = 1600;
	int height = 1200;
	string title = "default title";
	GLFWwindow* window = nullptr;

	void setWidth(int value) {
		width = value;
	}

	void setHeight(int value) {
		height = value;
	}

	void setTitle(const std::string& value) {
		title = value;
	}

	void initialize() {
		if (inited) return;
		inited = true;
		window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
		if (!window) {
			Logger::error("Failed to Initialze Window (Window.cpp)");
		}
		glfwMakeContextCurrent(window);
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			Logger::error("Failed to Initialize GLAD (Window.cpp)");
		}
		glfwSwapInterval(1);
	}

	GLFWwindow* getWindow() {
		return window;
	}

	void destroy() {
		glfwDestroyWindow(window);
		glfwTerminate();
	}
}