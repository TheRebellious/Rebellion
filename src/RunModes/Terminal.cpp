#include "Terminal.h"

Terminal::Terminal()
{
	command_list = {
		"exit",
		"help",
		"search",
	};
}

void Terminal::handleExit() {
	std::cout << "Exiting terminal." << std::endl;
	exit(0);
}

void Terminal::handleHelp() {
	for (const auto& cmd : command_list) {
		std::cout << "- " << cmd << std::endl;
	}
}

void Terminal::handleSearch(string args) {
	WebService ws;
	string response = ws.performGetRequest(args);
	displayMessage(response);
	if (response.empty()) {
		displayMessage("Search failed or returned no results.");
	} else {
		displayMessage("Search results:\n" + response);
	}
}

void Terminal::displayMessage(const string& message)
{
	std::cout << message << std::endl;
}

void Terminal::handleCommand(string command) {
	if (command == "exit") {
		handleExit();
	} else if (command == "help") {
		handleHelp();
	} else if (command == "search") {
		handleSearch(command.substr(command.find(" ") + 1));
	}
}

void Terminal::start()
{
	std::string input;
	while (std::getline(std::cin, input)) { // quit the program with ctrl-d
		string cmd = input.substr(0, input.find(" "));
		if (find(command_list.begin(), command_list.end(), cmd) != command_list.end()) {
			handleCommand(cmd);
		}
		else if (input.empty()) {
			// Ignore empty input
		}
		else {
			displayMessage("Unknown command: " + input);
		}
	}
}
