#include "fileReader.hpp"
#include "AaSequence.hpp"
#include <cstdio>
#include <iostream>
#include <memory>
#include <string>
#include <fstream>
#include <utility>
#include "RNA.hpp"
#include "DNA.hpp"

std::shared_ptr<std::ifstream> fileReader::openFile(const std::string &file){

	std::shared_ptr<std::ifstream> op_file = std::make_shared<std::ifstream>(file);
	if (!op_file->is_open()) {
		std::cerr << "Error opening file " << file << std::endl;
		return nullptr;
	}
	printf("I work\n");
	return op_file;
}

template<typename T>
std::vector<std::unique_ptr<typename T::BaseType>> fileReader::ReadFile(const std::string &file){

	std::vector<std::unique_ptr<typename T::BaseType>> results;
	auto op_file = fileReader::openFile(file);

	if (!op_file)
		return {};

	std::string id_info, line, id, seq;
	bool inSeq = false;

	while (std::getline(*op_file, line) ) {
		if (line.empty()) continue;
		if (line.starts_with('>')){
			if (inSeq){
				results.push_back(std::make_unique<T>(std::move(id), std::move(id_info), std::move(seq)));
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

		results.push_back(std::make_unique<T>(std::move(id), std::move(id_info), std::move(seq)));
	}
	return results;
}

template std::vector<std::unique_ptr<NtSequence>> fileReader::ReadFile<DNA>(const std::string&);
template std::vector<std::unique_ptr<NtSequence>> fileReader::ReadFile<RNA>(const std::string&);
template std::vector<std::unique_ptr<aaSequence>> fileReader::ReadFile<aaSequence>(const std::string&);

template<typename T>
std::vector<size_t> fileReader::ReadWithMotiff(const std::string &file){
	
	auto op_file = fileReader::openFile(file);

	if (!op_file)
		return {};
	std::string motiff, sequence, id, id_info;	
	std::getline(*op_file, sequence);
	std::getline(*op_file, motiff);
	
	std::unique_ptr<NtSequence> MotifSeq;
	MotifSeq = std::make_unique<T>(std::move(sequence));

	return MotifSeq->FindMotiff(motiff);
}
template std::vector<size_t> fileReader::ReadWithMotiff<DNA>(const std::string&);
template std::vector<size_t> fileReader::ReadWithMotiff<RNA>(const std::string&);

