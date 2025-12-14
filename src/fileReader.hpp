#pragma once

#include <fstream>
#include <memory>
#include <string>
#include <vector>

class fileReader {
public:

	static std::shared_ptr<std::ifstream> openFile(const std::string &file);

	template<typename T>
	static std::vector<std::unique_ptr<typename T::BaseType>> ReadFile(const std::string &file);

	template<typename T>
	static std::vector<size_t> ReadWithMotiff(const std::string &file);

};
