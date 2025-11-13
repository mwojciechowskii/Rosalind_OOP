#include "sequence.hpp"
#include <algorithm>
#include <cstddef>
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

Sequence::NtAmount Sequence::CntNt (){

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

std::string Sequence::Complement(){

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

size_t Sequence::HammingDist(const Sequence& other){

	size_t len = std::min(Seq.size(), other.Seq.size());
	size_t dist = 0;
	for (size_t i =0; i < len; i++){
		dist += (Seq[i] != other.Seq[i]);
	}
	return dist;
}
float Sequence::GCcontent () const{

	std::size_t sum = ntAmount.a;
	std::size_t GCsum = ntAmount.c + ntAmount.g;
	if (ntAmount.t.has_value()){
		sum += *ntAmount.t;	
	} else if (ntAmount.u.has_value()){
		sum += *ntAmount.u;
	}
	sum += GCsum;
	return (static_cast<float>(GCsum)/sum) * 100.0f;
}

//template<typename SeqType>
//static const SeqType* HighestGC(const std::vector<std::unique_ptr<SeqType>>& sequences){
//	
//	if(sequences.empty())
//		return nullptr;
//	auto maxGCval = std::max_element(sequences.begin(), sequences.end(), CompareGC<SeqType>);
//	return maxGCval->get();
//}
