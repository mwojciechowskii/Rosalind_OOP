#include "Sequence.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


std::string Sequence::file_read(const std::string &file) {
	std::ifstream op_file(file);
	if (!op_file.is_open()) {
		std::cerr << "Error opening file " << file << std::endl;
		return "";
	}

	std::ostringstream seq;
	seq << op_file.rdbuf();
	return seq.str();
}
