#include "Terminal.h"

#include <cctype>
#include <cstdlib>
#include <iomanip>

namespace
{
	string trim(const string &value)
	{
		int first = value.find_first_not_of(" \t\r\n");
		if (first == string::npos)
		{
			return {};
		}
		int last = value.find_last_not_of(" \t\r\n");
		return value.substr(first, last - first + 1);
	}

	string getCenteredText(const string &text, const int width, const int subtract = 0)
	{
		if (width <= subtract)
		{
			return {};
		}

		int contentWidth = static_cast<size_t>(width - subtract);
		int visibleLength = text.length() > contentWidth
								? contentWidth
								: text.length();

		string visibleText = text.substr(0, visibleLength);
		int remaining = contentWidth - visibleLength;
		int leftPadding = remaining / 2;
		int rightPadding = remaining - leftPadding;

		return string(leftPadding, ' ') +
			   visibleText +
			   string(rightPadding, ' ');
	}

	void printBorder(const int width)
	{
		std::cout << "+" + string(width - 2, '-') + "+" << std::endl;
	}

	void printRow(const string &text, const int width)
	{
		std::cout << "| " << getCenteredText(text, width, 3) << "|" << std::endl;
	}
}

void Terminal::displayMenu() const
{
	const auto [width, height] = getTerminalSize();

	printBorder(width);
	printRow("Rebellion", width);
	printRow("Terminal mode", width);
	printBorder(width);
	printRow("Commands", width);
	printRow("help: Show menu", width);
	printRow("search <url>: Fetch page text", width);
	printRow("lookup <term>: Search for a term on the preferred search engine", width);
	printRow("exit: Close app", width);
	printBorder(width);
	printRow("Type a command and press Enter.", width);
	printBorder(width);
}

void Terminal::handleExit()
{
	std::cout << "Exiting terminal." << std::endl;
	std::exit(0);
}

void Terminal::handleHelp()
{
	displayMenu();
}

void Terminal::handleSearch(const string &args)
{
	if (args.empty())
	{
		displayMessage("Usage: search <url>");
		return;
	}

	WebService ws;
	const string response = ws.performGetRequest(args);
	if (response.empty())
	{
		displayMessage("No readable page text found (request failed or page was empty).");
		return;
	}

	displayMessage("Page text:\n" + response);
}

void Terminal::displayMessage(const string &message)
{
	std::cout << message << std::endl
			  << std::endl;
}

void Terminal::handleCommand(const string &command, const string &args)
{
	if (command == "exit")
	{
		handleExit();
	}
	else if (command == "help")
	{
		handleHelp();
	}
	else if (command == "search")
	{
		handleSearch(args);
	}
}

pair<int, int> Terminal::getTerminalSize() const
{
	int columns, rows;
#ifdef _WIN32
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
#else
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	columns = w.ws_col;
	rows = w.ws_row;
#endif
	return {columns, rows};
}

void Terminal::start()
{
	displayMenu();
	string input;
	while (std::cout << "> " << std::flush, std::getline(std::cin, input))
	{
		input = trim(input);
		if (input.empty())
		{
			continue;
		}

		const auto separator = input.find_first_of(" \t");
		const string command = input.substr(0, separator);
		const string args = separator == string::npos
								? string{}
								: trim(input.substr(separator + 1));

		if (command == "exit" || command == "help" || command == "search")
		{
			handleCommand(command, args);
		}
		else
		{
			displayMessage("Unknown command: " + command + ". Type 'help' to see commands.");
		}
	}
	std::cout << std::endl;
}
