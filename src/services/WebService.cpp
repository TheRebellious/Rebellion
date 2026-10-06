#include "WebService.h"
#include <sstream>

WebService::WebService() {}

static size_t WriteCallback(char* data, size_t size, size_t nmemb, void* userp) {
    std::ostringstream* oss = static_cast<std::ostringstream*>(userp);
    oss->write(data, size * nmemb);
    return size * nmemb;
}

string WebService::performGetRequest(const std::string& requestUrl) {
    curl_global_init(CURL_GLOBAL_DEFAULT);
    CURL* handle = curl_easy_init();

    curl_easy_setopt(handle, CURLOPT_URL, requestUrl.c_str());
    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, WriteCallback);

    std::ostringstream response;
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, &response);

    CURLcode result = curl_easy_perform(handle);

    if (result != CURLE_OK) {
        std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(result) << std::endl;
    }

    curl_easy_cleanup(handle);
    curl_global_cleanup();

    return response.str();
}