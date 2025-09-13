#include "Window.h"

Window::Window() : size{ 800, 600 }, shapes(nullptr) {
	initialiseWindow();
}

Window::Window(Size size) : size(size), shapes(nullptr) {
	initialiseWindow();
}

Window::~Window() {
	for (int i = 0; i < shapeCount; ++i) {
		delete shapes[i]; // assuming ownership
	}
	delete[] shapes;
	if (glfw_window) {
		glfwDestroyWindow(glfw_window);
		glfwTerminate();
	}
}

void Window::initialiseWindow() {
	open();
}

int Window::open() {
	if (!glfwInit()) {
		return -1;
	}

	glfw_window = glfwCreateWindow(size.width, size.height, "Rebellion", nullptr, nullptr);
	if (!glfw_window) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(glfw_window);
	return 0;
}

void Window::update() {
	glClear(GL_COLOR_BUFFER_BIT);

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	drawShapes();

	glfwSwapBuffers(glfw_window);
	glfwPollEvents();

	if (glfwWindowShouldClose(glfw_window)) close();
}

void Window::close() {
	if (glfw_window) {
		glfwDestroyWindow(glfw_window);
		glfw_window = nullptr;
		glfwTerminate();
	}
}

void Window::drawShapes() {
	for (int i = 0; i < shapeCount; ++i) {
		shapes[i]->draw();
	}
}

void Window::addShape(Shape* shape) {
	Shape** newShapes = new Shape * [shapeCount + 1];

	for (int i = 0; i < shapeCount; ++i) {
		newShapes[i] = shapes[i];
	}

	newShapes[shapeCount] = shape;

	delete[] shapes;

	shapes = newShapes;
	shapeCount++;
}

void Window::removeShape(Shape* shape) {
	for (int i = 0; i < shapeCount; ++i) {
		if (shapes[i] == shape) {
			delete shapes[i];
			Shape** newShapes = new Shape * [shapeCount - 1];

			for (int j = 0; j < i; ++j) {
				newShapes[j] = shapes[j];
			}
			for (int j = i + 1; j < shapeCount; ++j) {
				newShapes[j - 1] = shapes[j];
			}

			delete[] shapes;
			shapes = newShapes;
			shapeCount--;
			return;
		}
	}
}
