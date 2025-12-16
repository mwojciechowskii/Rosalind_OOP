#pragma once

#include <optional>
#include <string>

class Request {
private:
	std::string RESPONSE;
	std::string URL;
public:
    Request(std::string& inURL): URL(inURL){}; 
    ~Request() = default; 
	std::optional<std::string> fetchFasta(std::string proteinID, long timeout_seconds = 10);
	std::string responseToSequence(const std::string& response);
};
