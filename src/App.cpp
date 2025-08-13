#include "App.h"

void runApp() {
	// Ensure the console window is hidden on Windows
#if defined(_WIN32) || defined(_WIN64)
	FreeConsole();
#endif

	Window mainWindow(Size{ 1280, 720 });

	while (true) {
		mainWindow.update();
	}
}

int main() {
	runApp();
}
