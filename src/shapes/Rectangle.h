#pragma once
#include "Shape.h"

class Rectangle : public Shape {
protected:
	Size size;

public:
	Rectangle(Point pos, Size size, Color color);

	void draw() override;
};
