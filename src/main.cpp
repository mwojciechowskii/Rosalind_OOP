#include "sequence.hpp"
#include <iostream>

std::string dnaFile = "./data/rosalind_revc.txt";

int main(){

	Sequence MyObject(dnaFile);
	MyObject.PrintStatistics(MyObject.CntNt());
	MyObject.PrintRNA(MyObject.Transcribe());
	std::cout << MyObject.ComplementDNA() << std::endl;


	return 0;
}
