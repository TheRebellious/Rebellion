#pragma once
#include <GLFW/glfw3.h>

struct Color {
	float r, g, b;
};

struct Size {
	int width, height;
};

struct Point {
	float x, y;
};

class Shape {
protected:
	Point pos;
	Color bgColour;
	bool visible = true;

public:
	Shape(Point pos, Color color);
	virtual ~Shape() = default;

	virtual void draw() = 0;

	float getX() const;
	float getY() const;
	Color getColor() const;

	void setPosition(float newX, float newY);
	void setColor(Color newColor);
	void setVisible(bool visiblility_state);
	bool isVisible() const;
};
