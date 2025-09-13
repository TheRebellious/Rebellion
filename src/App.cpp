#include "App.h"

ConfigLoader configLoader;

int main() {
	runApp(
		configLoader.getOption('w'),
		configLoader.getOption('h'),
		configLoader.getOption('m') == 1
	);
}


void runApp(int width, int height, bool createWindow) {
	if (createWindow) {
	// Ensure the console window is hidden on Windows
#if defined(_WIN32) || defined(_WIN64)
		FreeConsole();
#endif
		Window mainWindow(Size{ width, height });

		while (true) {
			mainWindow.update();
		}
	}
	else {
		Terminal terminal;
		terminal.start();
	}
}