#pragma once

#include <iostream>
#include <string>
#include "../services/WebService.h"

using namespace std;

class Terminal
{
public:
	Terminal() = default;
	void displayMessage(const string &message);
	void start();

private:
	void displayMenu() const;
	void handleCommand(const string &command, const string &args);
	void handleHelp();
	void handleSearch(const string &args);
	void handleExit();
	pair<int, int> getTerminalSize() const;
};
