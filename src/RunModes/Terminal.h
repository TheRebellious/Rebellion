#pragma once

#include <map>
#include <functional>
#include <iostream>
#include <string>

using namespace std;

class Terminal
{
public:
	Terminal();
	void displayMessage(const string& message);
	void start();
private:
	typedef std::map< std::string, std::function<void(void)> > command_dict;
	command_dict command_map;
	void handleHelp();
	void handleExit();
};