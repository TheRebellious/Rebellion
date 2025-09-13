#pragma once
#include <GLFW/glfw3.h>
#include "../shapes/Shape.h"

class Window {
private:
	Size size;
	GLFWwindow* glfw_window;
	Shape** shapes;
	int shapeCount = 0;

	void initialiseWindow();

public:
	Window();
	Window(Size size);
	~Window();

	int open();
	void update();
	void close();
	void drawShapes();
	void addShape(Shape* shape);
	void removeShape(Shape* shape);
};
