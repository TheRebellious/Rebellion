#include "ConfigLoader.h"

#include <fstream>
#include <sstream>

namespace
{
	/** Remove whitespace from both ends of a setting key or value. */
	std::string Trim(const std::string &text)
	{
		const auto first = text.find_first_not_of(" \t\r\n");
		if (first == std::string::npos)
			return {};

		const auto last = text.find_last_not_of(" \t\r\n");
		return text.substr(first, last - first + 1);
	}

	/** Parse an entire decimal integer, rejecting trailing non-whitespace text. */
	bool ParseInteger(const std::string &text, int &value)
	{
		const std::string trimmed = Trim(text);
		if (trimmed.empty())
			return false;

		std::istringstream input(trimmed);
		input >> value;
		return input && input.peek() == std::char_traits<char>::eof();
	}
}

ConfigLoader::ConfigLoader()
	: options{{"w", 1280}, {"h", 720}, {"m", 0}}
{
	options = loadConfig();

	// Create the file with defaults on first run.
	std::ifstream configFile(configFilePath);
	if (!configFile)
		saveConfig();
}

int ConfigLoader::getOption(const std::string &key) const
{
	const auto option = options.find(key);
	return option == options.end() ? 0 : option->second;
}

void ConfigLoader::setOption(const std::string &key, int value)
{
	options[key] = value;
	saveConfig();
}

ConfigLoader::Options ConfigLoader::loadConfig()
{
	Options loadedOptions{{"w", 1280}, {"h", 720}, {"m", 0}};
	std::ifstream configFile(configFilePath);
	if (!configFile)
		return loadedOptions;

	std::string line;
	while (std::getline(configFile, line))
	{
		const std::string trimmedLine = Trim(line);
		if (trimmedLine.empty() || trimmedLine.front() == '#')
			continue;

		const auto delimiter = trimmedLine.find('=');
		if (delimiter == std::string::npos)
			continue;

		const std::string key = Trim(trimmedLine.substr(0, delimiter));
		int value = 0;
		if (!key.empty() && ParseInteger(trimmedLine.substr(delimiter + 1), value))
			loadedOptions[key] = value;
	}

	return loadedOptions;
}

bool ConfigLoader::saveConfig() const
{
	std::ofstream configFile(configFilePath, std::ios::out | std::ios::trunc);
	if (!configFile)
		return false;

	for (const auto &[key, value] : options)
		configFile << key << '=' << value << '\n';

	return configFile.good();
}
