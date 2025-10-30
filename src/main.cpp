#include "sequence.hpp"

std::string dnaFile = "./data/rosalind_rna.txt";

int main(){

	Sequence MyObject(dnaFile);
	MyObject.PrintStatistics(MyObject.CntNt());
	MyObject.PrintRNA(MyObject.Transcribe());


	return 0;
}
