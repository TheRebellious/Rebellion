#pragma once

#include <list>
#include <functional>
#include <iostream>
#include <string>
#include "../services/WebService.h"

using namespace std;

class Terminal
{
public:
	Terminal();
	void displayMessage(const string& message);
	void start();
private:
	list<string> command_list;
	void handleCommand(string command);
	void handleHelp();
	void handleSearch(string args);
	void handleExit();
};