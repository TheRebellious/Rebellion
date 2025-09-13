#include <fstream>
#include <map>
#include <string>

#ifdef _WIN32
#include <io.h> 
#define access    _access_s
#else
#include <unistd.h>
#endif

using namespace std;

class ConfigLoader
{
public:
	ConfigLoader();
	int getOption(char option);
	void setOption(char option, int value);

private:
	map<char, int> options;
	const char* configFilePath = "config.cfg";
	fstream configFile;
	map<char, int> loadConfig();
	int saveConfig(map<char, int> options);
	bool fileExists(const std::string& Filename);
};
