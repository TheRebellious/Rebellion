// Rebellion.cpp : Defines the entry point for the application.
//
#include <GLFW/glfw3.h>
#include "Window.cpp"

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif

using namespace std;

int main() {
	// Ensure the console window is hidden on Windows
#if defined(_WIN32) || defined(_WIN64)
	FreeConsole();
#endif
	Window mainWindow = Window(Size(1280, 720));

	while (true) {
		mainWindow.update();
	}
}
