#include "Shape.h"

Shape::Shape(Point pos, Color color)
	: pos(pos), bgColour(color) {
}

float Shape::getX() const { return pos.x; }
float Shape::getY() const { return pos.y; }
Color Shape::getColor() const { return bgColour; }

void Shape::setPosition(float newX, float newY) {
	pos.x = newX;
	pos.y = newY;
}

void Shape::setColor(Color newColor) {
	bgColour = newColor;
}

void Shape::setVisible(bool visiblility_state) {
	visible = visiblility_state;
}

bool Shape::isVisible() const {
	return visible;
}
