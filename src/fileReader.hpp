#pragma once

#include <fstream>
#include <memory>
#include "sequence.hpp"
#include <string>
#include <vector>

class fileReader {
public:

	static std::shared_ptr<std::ifstream> openFile(const std::string &file);
	//template<class SeqType>
	static std::vector<std::unique_ptr<Sequence>> ReadFile(const std::string &file, Sequence::Type type);
	static std::unique_ptr<Sequence> createFromType(Sequence::Type type, std::string id, std::string id_info, std::string seq);

	static std::vector<size_t> ReadWithMotiff(const std::string &file, Sequence::Type type);

};
