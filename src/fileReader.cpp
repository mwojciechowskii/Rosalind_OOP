#include "fileReader.hpp"
#include "DNA.hpp"
#include "RNA.hpp"
#include <iostream>
#include <memory>
#include <string>
#include <fstream>
#include <utility>

template<typename SeqType>
std::vector<std::unique_ptr<SeqType>> fileReader::ReadFile(const std::string &file){

	std::vector<std::unique_ptr<SeqType>> results;

	std::ifstream op_file(file);
	if (!op_file.is_open()) {
		std::cerr << "Error opening file " << file << std::endl;
		return {};
	}
	std::string id_info, line, id, seq;
	bool inSeq = false;

	while (std::getline(op_file, line) ) {
		if (line.empty()) continue;
		if (line.starts_with('>')){
			if (inSeq){
				results.push_back(std::make_unique<SeqType>(std::move(id), std::move(id_info), std::move(seq)));
				seq.clear();
			}
			std::string header = line.substr(1);
			unsigned long checker = header.find_first_of(" \t");
			if (checker != std::string::npos){
				id = header.substr(0, checker);
				id_info = header.substr(checker + 1);
			}
			else {
				id = std::move(header);
				id_info.clear();
			}
			inSeq = true;
		} else {
			if (inSeq){
				seq += (line);
			}
		}
	}
	if (inSeq){
		results.push_back(std::make_unique<SeqType>(std::move(id), std::move(id_info), std::move(seq)));
	}
	return results;
}
template std::vector<std::unique_ptr<DNA>> 
fileReader::ReadFile<DNA>(const std::string&);

template std::vector<std::unique_ptr<RNA>> 
fileReader::ReadFile<RNA>(const std::string&);
