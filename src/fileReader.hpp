#pragma once

#include <fstream>
#include <memory>
#include <string>
#include <vector>

class fileReader {
private:
	template<typename T>
	static void addRecord(std::vector<std::unique_ptr<typename T::BaseType>>& resultsOut, std::string& id, std::string& id_info, std::string& seq, size_t& plainCounter);
public:

	static std::shared_ptr<std::ifstream> openFile(const std::string &file);
	static std::unique_ptr<std::string> simpleRead(const std::string &file);

	template<typename T>
	static std::vector<std::unique_ptr<typename T::BaseType>> ReadFile(const std::string &file);

	template<typename T>
	static std::vector<size_t> ReadWithMotiff(const std::string &file);

};
