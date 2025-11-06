#include "sequence.hpp"
#include <algorithm>
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

Sequence::Sequence(const std::string &file)
: Seq(file_read(file)) {}

Sequence::NtAmount Sequence::CntNt (){

	//NtAmount test;
	ntAmount.t = 0;

	for (char &Nt : Seq){

		switch (Nt){
			default:
				break;
			case 'T': case 't' :
				++*ntAmount.t;
				break;
			case 'A': case 'a':
				++ntAmount.a;
				break;
			case 'G': case 'g':
				++ntAmount.g;
				break;
			case 'C': case 'c':
				++ntAmount.c;
				break;
		}
	}
	return ntAmount;
}

std::string Sequence::ComplementDNA(){

	std::string CompSeq;
	for (char nt : Seq){

		switch (nt) {
			default:
			break;
			case 'A': case 'a':
				CompSeq.push_back('T');
				break;

			case 'T': case 't':
				CompSeq.push_back('A');
				break;
			case 'G': case 'g':
				CompSeq.push_back('C');
				break;
			case 'C': case 'c':
				CompSeq.push_back('G');
				break;
			}	
	}
	std::reverse(CompSeq.begin(), CompSeq.end());
	return CompSeq;

}
