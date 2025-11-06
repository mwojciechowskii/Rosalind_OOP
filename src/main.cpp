#include "sequence.hpp"
#include <iostream>

//TODO
//private rna and dna strings with publicly visible string
std::string dnaFile = "./data/rosalind_revc.txt";

int main(){

	Sequence MyObject(dnaFile);
	MyObject.CntNt();

	std::cout << *MyObject.ntAmount.t << std::endl;

	return 0;
}
