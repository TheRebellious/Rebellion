#pragma once

#include <GLFW/glfw3.h>
#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif

#include "Window.h"
#include "shapes/Rectangle.h"

// Function prototype for starting the app
void runApp();