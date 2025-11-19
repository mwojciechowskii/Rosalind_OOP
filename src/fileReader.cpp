#include "fileReader.hpp"
#include "DNA.hpp"
#include "RNA.hpp"
#include <cstdio>
#include <iostream>
#include <memory>
#include "sequence.hpp"
#include <string>
#include <fstream>
#include <utility>

std::shared_ptr<std::ifstream> fileReader::openFile(const std::string &file){

	std::shared_ptr<std::ifstream> op_file = std::make_shared<std::ifstream>(file);
	if (!op_file->is_open()) {
		std::cerr << "Error opening file " << file << std::endl;
		return nullptr;
	}
	printf("I work\n");
	return op_file;
}

std::unique_ptr<Sequence> fileReader::createFromType(Sequence::Type type, std::string id, std::string id_info, std::string seq){

if (type == Sequence::Type::DNA) return std::make_unique<DNA>(std::move(id), std::move(id_info), std::move(seq));
if (type == Sequence::Type::RNA) return std::make_unique<RNA>(std::move(id), std::move(id_info), std::move(seq));
return nullptr;
}
//template<typename Sequence>
std::vector<std::unique_ptr<Sequence>> fileReader::ReadFile(const std::string &file, Sequence::Type type){

	std::vector<std::unique_ptr<Sequence>> results;
	auto op_file = fileReader::openFile(file);

	if (!op_file)
		return {};

	std::string id_info, line, id, seq;
	bool inSeq = false;

	while (std::getline(*op_file, line) ) {
		if (line.empty()) continue;
		if (line.starts_with('>')){
			if (inSeq){
				results.push_back(createFromType(type, std::move(id), std::move(id_info), std::move(seq)));
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
		results.push_back(createFromType(type, std::move(id), std::move(id_info), std::move(seq)));
	}
	return results;
}

//template std::vector<std::unique_ptr<DNA>> 
//fileReader::ReadFile<DNA>(const std::string&);
//
//template std::vector<std::unique_ptr<RNA>> 
//fileReader::ReadFile<RNA>(const std::string&);


std::vector<size_t> fileReader::ReadWithMotiff(const std::string &file, Sequence::Type type){
	
	auto op_file = fileReader::openFile(file);

	if (!op_file)
		return {};
	std::string motiff, sequence, id, id_info;	
	std::getline(*op_file, sequence);
	std::getline(*op_file, motiff);
	
	std::unique_ptr<Sequence> MotifSeq;
	if (type == Sequence::Type::DNA){
		MotifSeq = std::make_unique<DNA>(std::move(sequence));
		return MotifSeq->FindMotiff(motiff);
	}
	if (type == Sequence::Type::RNA){
		MotifSeq = std::make_unique<RNA>(std::move(sequence));
		return MotifSeq->FindMotiff(motiff);
	}
	return {};
}
