#pragma once

#include <map>
#include <string>

/** Loads and saves the application's string-keyed integer settings. */
class ConfigLoader
{
public:
	ConfigLoader();

	/** Return the setting for key, or zero when the key is not present. */
	int getOption(const std::string &key) const;

	/** Update a setting and save all settings to the configuration file. */
	void setOption(const std::string &key, int value);

private:
	using Options = std::map<std::string, int>;

	Options options;
	const std::string configFilePath = "config.cfg";

	Options loadConfig();
	bool saveConfig() const;
};
