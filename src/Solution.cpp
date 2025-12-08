#include "Solution.hpp"
#include "DNA.hpp"
#include "fileReader.hpp"
#include <cstddef>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <memory>
#include "Sequence.hpp"

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
	auto opened_seq = fileReader::ReadFile<NtSequence>(file, Type::DNA);
	for (auto &sequence: opened_seq){

		std::cout << std::fixed << std::setprecision(6);
		std::cout << sequence->GCcontent() << std::endl;
	}
	const auto maxGC = NtSequence::HighestGC(opened_seq);

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

void Solution::RabbitsRec(){

	/* Problem:
	https://rosalind.info/problems/fib/
	*/
	std::string file = "./data/rosalind_fib.txt";
	auto op_file = fileReader::openFile(file);
	size_t n{0}, k{0};
	*op_file >> n >> k;

	if (n <= 0){
		std::cout << "0" << '\n';
		return;
	}
	if (n == 1 || n == 2){
		std::cout << "1" << '\n';
		return;
	}
	size_t cur{0}, prev1{1}, prev2{1};
	for (size_t i = 3; i <=n; i++){
		cur = prev1 + k * prev2;
        prev2 = prev1;
        prev1 = cur;
	}
	std::cout << cur << std::endl;
	return;
}

float Solution::recessive_prob(size_t sum_outcomes, size_t hetero, size_t homo_rec){

	float recessive_prob{0};

	return recessive_prob;
}

void Solution::MendelLaw(){
	
	/* Problem:
	https://rosalind.info/problems/iprb/
	*/

	std::string file = "./data/rosalind_iprb.txt";
	auto op_file = fileReader::openFile(file);

	// dominant, recessive and heterozygous
	float Homo_dom{0}, Homo_rec{0}, Hetero{0};
	*op_file >> Homo_dom >> Hetero >> Homo_rec;
	
	float pop_sum = Homo_dom + Homo_rec + Hetero;
	float sumAll = pop_sum * (pop_sum - 1) / 2 ;

	float allDominant = Homo_dom * (Homo_dom - 1) / 2;
	float DominantHetero = Homo_dom * Hetero;
	float DominantRecessive = Homo_dom * Homo_rec; 
	float HeteroOnly = Hetero * (Hetero - 1) / 2;
	float HeteroHomoRec = Hetero * Homo_rec;
	//HomoRecessive wont add anything to the result

	float probability = (allDominant + DominantHetero + DominantRecessive) / sumAll;

	probability += (HeteroOnly * 3/4) / sumAll;
	probability += (HeteroHomoRec * 1/2) / sumAll;

	std::cout << probability << std::endl;
}
