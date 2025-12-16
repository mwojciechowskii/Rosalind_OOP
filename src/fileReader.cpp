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
#include <sstream>

std::unique_ptr<std::string> fileReader::simpleRead(const std::string &file) {

	auto opFile = fileReader::openFile(file);

	std::ostringstream seq;
	seq << opFile->rdbuf();
	std::string s =seq.str();
	return std::make_unique<std::string>(std::move(s));
}

std::shared_ptr<std::ifstream> fileReader::openFile(const std::string &file){

	std::shared_ptr<std::ifstream> op_file = std::make_shared<std::ifstream>(file);
	if (!op_file->is_open()) {
		std::cerr << "Error opening file: " << file << std::endl;
		return nullptr;
	}
	return op_file;
}

template<typename T>
void fileReader::addRecord(std::vector<std::unique_ptr<typename T::BaseType>>& resultsOut, std::string& id, std::string& id_info, std::string& seq, size_t& plainCounter) {

	if (seq.empty())
		return;

	if (id.empty()) {
		if (plainCounter == 0) {
			id = "unknownSeq";
		} else {
			id = "unknownSeq" + std::to_string(plainCounter);
		}
	}

	resultsOut.emplace_back(std::make_unique<T>(std::move(id), std::move(id_info), std::move(seq)));

	id.clear();
	id_info.clear();
	seq.clear();
	++plainCounter;
}

template void fileReader::addRecord<DNA>(std::vector<std::unique_ptr<typename DNA::BaseType>>&, std::string&, std::string&, std::string&, size_t&plainCounter);
template void fileReader::addRecord<RNA>(std::vector<std::unique_ptr<typename RNA::BaseType>>&, std::string&, std::string&, std::string&, size_t&);
template void fileReader::addRecord<aaSequence>(std::vector<std::unique_ptr<typename aaSequence::BaseType>>&, std::string&, std::string&, std::string&, size_t&);

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



template<typename T>
std::vector<std::unique_ptr<typename T::BaseType>> fileReader::ReadFile(const std::string &file){

	std::vector<std::unique_ptr<typename T::BaseType>> results;
	auto op_file = fileReader::openFile(file);

	if (!op_file)
		return {};

	std::string id_info, line, id, seq;
	//TODO zamiast bool, bitshifting
	bool inSeq = false;
	bool plainMode = false;
	size_t plainCounter = 0;

	while (std::getline(*op_file, line) ) {
		if (line.empty()) continue;
		if (!inSeq && !plainMode){
			if (line.starts_with('>')){
				plainMode = false;
			}else{
				plainMode = true;
				seq = line;
				inSeq = true;
				continue;
			}
		}
	if (!plainMode){
		if (line.starts_with('>')){
			addRecord<T>(results, id, id_info, seq, plainCounter);
			std::string header = line.substr(1);
			std::size_t pos = header.find_first_of(" \t");
			if (pos != std::string::npos) {
				id = header.substr(0, pos);
				id_info = header.substr(pos + 1);
			} else {
				id = std::move(header);
				id_info.clear();
			}
			inSeq = true;
		} else {
			if (inSeq)
				seq += line;
		}
		continue;
	}
		bool isWhitespace = false;
        for (char c : line) {
            if (std::isspace(static_cast<unsigned char>(c))) {
                isWhitespace = true;
                break;
            }
        }
	if (isWhitespace){
		addRecord<T>(results, id, id_info, seq, plainCounter);
		size_t firstNonWs = line.find_first_not_of(" \t");
		if (firstNonWs != std::string::npos) {
			seq = line.substr(firstNonWs);
			inSeq = true;
		} else {
			inSeq = false;
            }
        } else {
            seq += line;
            inSeq = true;
        }
    }
    addRecord<T>(results, id, id_info, seq, plainCounter);

    return results;
}

template std::vector<std::unique_ptr<NtSequence>> fileReader::ReadFile<DNA>(const std::string&);
template std::vector<std::unique_ptr<NtSequence>> fileReader::ReadFile<RNA>(const std::string&);
template std::vector<std::unique_ptr<aaSequence>> fileReader::ReadFile<aaSequence>(const std::string&);
