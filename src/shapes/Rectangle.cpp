#include <GLFW/glfw3.h>
#include "Global.h"

class Rectangle {
private:
	float x, y;
	float width, height;
	Color bgColour;

public:
	Rectangle(float x, float y, float width, float height, Color color)
		:x(x), y(y), width(width), height(height), bgColour(color) {


	}

	void draw() {
		glColor3f(bgColour.r, bgColour.g, bgColour.b);
		glBegin(GL_QUADS);

		// anchor at top-left corner
		glVertex2f(x, y);
		glVertex2f(x + width, y);
		glVertex2f(x + width, y + height);
		glVertex2f(x, y + height);

		glEnd();
	}
};