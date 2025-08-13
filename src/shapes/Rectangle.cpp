#include "Rectangle.h"

Rectangle::Rectangle(Point pos, Size size, Color color)
	: Shape(pos, color), size(size) {
}

void Rectangle::draw() {
	glColor3f(bgColour.r, bgColour.g, bgColour.b);
	glBegin(GL_QUADS);

	// Anchor at top-left corner
	glVertex2f(pos.x, pos.y);
	glVertex2f(pos.x + size.width, pos.y);
	glVertex2f(pos.x + size.width, pos.y + size.height);
	glVertex2f(pos.x, pos.y + size.height);

	glEnd();
}
