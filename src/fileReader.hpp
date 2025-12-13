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

//	template<typename T>
//	static std::unique_ptr<T> createFromType(Sequence::Type type, std::string id, std::string id_info, std::string seq);

	template<typename T>
	static std::vector<size_t> ReadWithMotiff(const std::string &file);

};
