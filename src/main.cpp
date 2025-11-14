#include "sequence.hpp"
#include "DNA.hpp"
#include "fileReader.hpp"
#include <iomanip>
#include <iostream>

std::string file = "./data/rosalind_gc.txt";


int main(){

	auto opened_seq = fileReader::ReadFile<DNA>(file);
	for (auto &sequence: opened_seq){
		auto counts = sequence->CntNt();
	

		std::cout << std::fixed << std::setprecision(6);
		std::cout << sequence->GCcontent() << std::endl;
	}
	const auto maxGC = Sequence::HighestGC(opened_seq);

	std::cout << maxGC->get_id() << std::endl;
    std::cout << std::fixed << std::setprecision(6) << maxGC->GCcontent() << '\n';

	return 0;
}
