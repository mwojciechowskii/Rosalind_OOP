#include "sequence.hpp"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>


std::string Sequence::file_read(const std::string &file) {
	std::ifstream op_file(file);
	if (!op_file.is_open()) {
		std::cerr << "Error opening file " << file << std::endl;
		return "";
	}

	std::string seq;
	std::string line;
	while (std::getline(op_file, line)) {
		seq += line;
	}
	return seq;
}

Sequence::Sequence(const std::string &file)
: Seq(file_read(file))
{}

Sequence::NtAmount Sequence::CntNt (){

	NtAmount Result = {.a = 0, .t = 0, .g = 0, .c = 0};

	for (char &Nt : Seq){

		switch (Nt){
			default:
				break;
			case 'T': case 't' :
				Result.t++;
				break;
			case 'A': case 'a':
				Result.a++;
				break;
			case 'G': case 'g':
				Result.g++;
				break;
			case 'C': case 'c':
				Result.c++;
				break;
				

		}

	}
	return Result;
}

void Sequence::PrintStatistics(const Sequence::NtAmount &ntamount){
	
	std::cout << ntamount.a << " " << ntamount.c << " " << ntamount.g << " " << ntamount.t << std::endl;

}

std::string Sequence::Transcribe(){

	std::string Rna;
	
	for (char nt: Seq){

		switch (nt) {
			default:
				break;
			case 'a': case 'A':
				Rna.push_back('A');
				break;
			case 't': case 'T':
				Rna.push_back('U');
				break;
			case 'c': case 'C':
				Rna.push_back('C');
				break;

			case 'g': case 'G':
				Rna.push_back('G');
				break;
		}
	}

	return Rna;
}

void Sequence::PrintRNA(std::string RNAseq){

	std::cout << RNAseq << std::endl;
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
