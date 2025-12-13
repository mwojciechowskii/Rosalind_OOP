#include "Solution.hpp"
#include "fileReader.hpp"
#include <cstddef>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <memory>
#include "DNA.hpp"

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
	auto opened_seq = fileReader::ReadFile<DNA>(file);
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
	auto op_file = fileReader::ReadWithMotiff<DNA>(file);

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

double Solution::MendelHelper(double allele){

	return allele * (allele - 1) / 2;
}

void Solution::MendelLaw(){
	
	/* Problem:
	https://rosalind.info/problems/iprb/
	*/

	std::string file = "./data/rosalind_iprb.txt";
	auto op_file = fileReader::openFile(file);

	// dominant, recessive and heterozygous
	double Homo_dom{0}, Homo_rec{0}, Hetero{0};
	*op_file >> Homo_dom >> Hetero >> Homo_rec;
	
	double pop_sum = Homo_dom + Homo_rec + Hetero;
	double sumAll = MendelHelper(pop_sum);

	double allDominant = MendelHelper(Homo_dom);
	double DominantHetero = Homo_dom * Hetero;
	double DominantRecessive = Homo_dom * Homo_rec; 
	double HeteroOnly = MendelHelper(Hetero);
	double HeteroHomoRec = Hetero * Homo_rec;
	//HomoRecessive wont add anything to the result

	double probability = (allDominant + DominantHetero + DominantRecessive) / sumAll;

	probability += (HeteroOnly * 0.75) / sumAll;
	probability += (HeteroHomoRec * 0.5) / sumAll;

	std::cout << probability << std::endl;
}

void Solution::Translation(){

	std::string file = "./data/rosalind_prot.txt";
	auto openedSeq = fileReader::ReadFile<RNA>(file);
	std::vector<std::unique_ptr<aaSequence>> translatedSequence;
	translatedSequence.reserve(openedSeq.size());

	for (auto &sequence: openedSeq){

		auto translated = sequence->Translate();

		std::cout << translated->get_seq() << std::endl;
		translatedSequence.push_back(std::move(translated));
	} 

}
