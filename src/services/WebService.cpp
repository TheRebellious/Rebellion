#include "WebService.h"

WebService::WebService() {
	curl_global_init(CURL_GLOBAL_DEFAULT);
}

static size_t
WriteCallback(
	char* receivedData,
	size_t dataSize,
	size_t dataBlocks,
	void* outputBuffer
) {
	std::string* strBuffer = static_cast<std::string*>(outputBuffer);
	strBuffer->append(receivedData, dataSize * dataBlocks);
	return dataSize * dataBlocks;
}

string WebService::performGetRequest(
    const std::string& requestUrl
) {
    CURL* curlHandle = curl_easy_init();
    if (curlHandle) {
        CURLcode result;
        std::string responseBuffer;

        curl_easy_setopt(curlHandle, CURLOPT_URL, requestUrl.c_str());
        curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, &responseBuffer);
        curl_easy_setopt(curlHandle, CURLOPT_HTTPGET, 1L);

        result = curl_easy_perform(curlHandle);
        if (result != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: "
                << curl_easy_strerror(result) << std::endl;
        }
        else {
            std::cout << "GET Request Output: " << responseBuffer << std::endl;
        }

        curl_easy_cleanup(curlHandle);
    }
}