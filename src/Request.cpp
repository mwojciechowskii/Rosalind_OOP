#include "Request.hpp"
#include <cstdio>
#include <curl/curl.h>
#include <curl/easy.h>
#include <iostream>
#include <optional>
#include <string>
#include <sstream>

size_t writeToSTR(void *ptr, size_t size, size_t nmemb, std::string *s) {
/* thank god for stackoverflow
https://stackoverflow.com/questions/2329571/c-libcurl-get-output-into-a-string */

	s->append(static_cast<char *>(ptr), size*nmemb);
	return size*nmemb;
}

/*TODO
* FIX THIS */
std::string Request::responseToSequence(const std::string& response){

    std::istringstream issResponse(response);
    std::string line, seq;

    while (std::getline(issResponse, line)){
        if (line.empty()) continue;
        if (line.starts_with('>')){
			seq.append(line);
            seq.push_back('\n');
		}
        for (char c : line){
			if (!std::isspace(static_cast<unsigned char>(c)))
				seq.push_back(c);
		}
    }
    return seq;
}

std::optional<std::string> Request::fetchFasta(std::string proteinID, long timeout_seconds){
	
	std::string fullURL = URL + proteinID + ".fasta";

	CURL* curl = curl_easy_init();
	if (!curl) return std::nullopt;

	std::string response;

	curl_easy_setopt(curl, CURLOPT_URL, fullURL.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeToSTR);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout_seconds);

	CURLcode res = curl_easy_perform(curl);
	long httpCode = 0;
	curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
	if(res != CURLE_OK){
		fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
		return std::nullopt;
	}
	if (httpCode != 200){
		std::cerr << stderr << "HTTP return code: " << httpCode << " while fetching: " << proteinID << std::endl;
		return std::nullopt;
	}

	curl_easy_cleanup(curl);
	RESPONSE = response;

	return response;
}
