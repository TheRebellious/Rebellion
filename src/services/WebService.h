#pragma once

#include <curl/curl.h>
#include <string>
#include <iostream>

using namespace std;

class WebService {
public:
	WebService();
	string performGetRequest(const std::string& requestUrl);
};