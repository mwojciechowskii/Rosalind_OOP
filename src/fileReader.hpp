#pragma once

#include <memory>
#include <string>
#include <vector>

class fileReader {
private:
public:
	fileReader(std::string &file); 
	~fileReader() = default; 

	template<class SeqType>
	static std::vector<std::unique_ptr<SeqType>> ReadFile(const std::string &file);

	static std::vector<int> ReadWithMotiff(const std::string &file);

};
