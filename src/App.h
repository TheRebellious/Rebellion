#pragma once

#include <GLFW/glfw3.h>
#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif

#include "RunModes/Window.h"
#include "RunModes/Terminal.h"
#include "shapes/Rectangle.h"
#include "services/ConfigLoader.h"

// Function prototype for starting the app
void runApp(int width, int height, bool createWindow);