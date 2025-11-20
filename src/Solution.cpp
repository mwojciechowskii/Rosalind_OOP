#include "Solution.hpp"
#include "DNA.hpp"
#include "fileReader.hpp"
#include <iomanip>
#include <iostream>
#include <memory>
#include "sequence.hpp"

using Type = Sequence::Type;

void Solution::HammingDist(){


	/* Problem:
	https://rosalind.info/problems/hamm/
	*/
	std::string file1 = "./data/seq1ham.txt";
	std::string file2 = "./data/seq2ham.txt";

	auto seqs = std::make_unique<DNA>(file1);
	auto seqs2 = std::make_unique<DNA>(file2); 

	std::cout << seqs->HammingDist(*seqs2) << '\n';
}

void Solution::GCcount(){

	/* Problem:
	https://rosalind.info/problems/gc/ 
	*/
	std::string file = "./data/rosalind_gc.txt";
	auto opened_seq = fileReader::ReadFile(file, Type::DNA);
	for (auto &sequence: opened_seq){

		std::cout << std::fixed << std::setprecision(6);
		std::cout << sequence->GCcontent() << std::endl;
	}
	const auto maxGC = Sequence::HighestGC(opened_seq);

	std::cout << maxGC->get_id() << std::endl;
    std::cout << std::fixed << std::setprecision(6) << maxGC->GCcontent() << '\n';
}

void Solution::FindMotiff(){

	/* Problem:
	https://rosalind.info/problems/subs/
	*/
	std::string file = "./data/rosalind_subs.txt";
	auto op_file = fileReader::ReadWithMotiff(file, Sequence::Type::DNA);

	for (size_t i = 0; i < op_file.size(); ++i) {
		if (i > 0) std::cout << " ";
		std::cout << op_file[i];
	}
	printf("\n");

}
