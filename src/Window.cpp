#include "shapes/Rectangle.cpp"

class Window {
private:
	Size size;
	GLFWwindow* glfw_window;

public:
	Window() : size{ 800, 600 } {
		open();
	}

	Window(Size size) : size(size) {
		open();
	}

	int open() {
		if (!glfwInit()) {
			return -1;
		}

		glfw_window = glfwCreateWindow(size.width, size.height, "Rebellion", nullptr, nullptr);
		if (!glfw_window) {
			glfwTerminate();
			return -1;
		}

		glfwMakeContextCurrent(glfw_window);
	}

	void update() {
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(glfw_window);
		glfwPollEvents();

		if (glfwWindowShouldClose(glfw_window)) close();
	}

	void close() {
		glfwDestroyWindow(glfw_window);
		glfwTerminate();
	}
};