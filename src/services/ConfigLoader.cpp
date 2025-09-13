#include "ConfigLoader.h"


ConfigLoader::ConfigLoader()
{
	options = {
		{'w', 1280},
		{'h', 720},
		{'m', 0}
	};
	loadConfig();
}

int ConfigLoader::getOption(char option)
{
	return options[option];
}

void ConfigLoader::setOption(char option, int value)
{
	options[option] = value;
	saveConfig(options);
}

map<char, int> ConfigLoader::loadConfig()
{
	if (fileExists(configFilePath)) {
		configFile.open(configFilePath, ios::in);
		std::string line;
		while (std::getline(configFile, line))
		{
			size_t delimiterPos = line.find('=');
			if (delimiterPos != std::string::npos)
			{
				char key = line[0];
				int value = std::stoi(line.substr(delimiterPos + 1));
				options[key] = value;
			}
		}
	}
	else {
		saveConfig(options);
	}
	return options;
}

int ConfigLoader::saveConfig(map<char, int> options)
{
	try
	{
		configFile.open(configFilePath, ios::out);
		for (const auto& p : options)
		{
			configFile << p.first << '=' << p.second << std::endl;
		}
		configFile.close();
		return 0;
	}
	catch (...)
	{
		return -1;
	}
}

bool ConfigLoader::fileExists(const std::string& Filename)
{
	return access(Filename.c_str(), 0) == 0;
}

