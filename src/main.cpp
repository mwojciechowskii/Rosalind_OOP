#include "sequence.hpp"
#include <iostream>

//TODO
//private rna and dna strings with publicly visible string
std::string dnaFile = "./data/seq1ham.txt";
std::string file2 = "./data/seq2ham.txt";


int main(){

	Sequence MyObject(dnaFile);
	Sequence New(file2);

	std::cout << MyObject.HammingDist(New) << std::endl;


	return 0;
}
