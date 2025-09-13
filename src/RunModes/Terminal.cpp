#include "Terminal.h"

Terminal::Terminal()
{
	command_map.insert({
		{"exit", [this]() { handleExit(); }},
		{"help", [this]() { handleHelp(); }},
	});
}

void Terminal::handleExit() {
	std::cout << "Exiting terminal." << std::endl;
	exit(0);
}

void Terminal::handleHelp() {
	for (const auto& cmd : command_map) {
		std::cout << "- " << cmd.first << std::endl;
	}
}

void Terminal::displayMessage(const string& message)
{
	std::cout << message << std::endl;
}

void Terminal::start()
{
	std::string input;
	while (std::getline(std::cin, input)) { // quit the program with ctrl-d
		auto it = command_map.find(input);
		if (it != end(command_map)) {
			(it->second)(); // execute the command
		}
		else {
			displayMessage("Unknown command: " + input);
		}
	}
}
