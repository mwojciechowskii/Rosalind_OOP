#include "Solution.hpp"
#include "fileReader.hpp"
#include "AaSequence.hpp"
#include <cstddef>
#include <cstdio>
#include "interface/Transcriptable.hpp"
#include "interface/Translatable.hpp"
#include <iomanip>
#include <iostream>
#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>
#include "DNA.hpp"
#include "Request.hpp"

void Solution::HammingDist(){
	/* Problem:
	https://rosalind.info/problems/hamm/
	*/
	std::string file1 = "./data/seq1ham.txt";
	std::string file2 = "./data/seq2ham.txt";

	auto rSeq = fileReader::simpleRead(file1);
	auto rSeq2 = fileReader::simpleRead(file2);

	auto seqs = std::make_unique<DNA>(std::move(*rSeq)); 
	auto seqs2 = std::make_unique<DNA>(std::move(*rSeq2)); 

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

	std::cout << maxGC->getID() << std::endl;
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

	/* Problem:
	https://rosalind.info/problems/prot/ 
	*/
	std::string file = "./data/rosalind_prot.txt";
	auto openedSeq = fileReader::ReadFile<RNA>(file);
	std::vector<std::unique_ptr<aaSequence>> translatedSequence;
	translatedSequence.reserve(openedSeq.size());

	for (auto &sequence: openedSeq){

		if (auto *t = dynamic_cast<Translatable*>(sequence.get())){
			auto translated = t->translate();
			std::cout << translated->getSeq() << std::endl;
			translatedSequence.push_back(std::move(translated));
		}
	} 
}

void Solution::CalcProteinMass(){

	/* Problem:
	https://rosalind.info/problems/prtm/
	*/

	std::string file = "./data/rosalind_prtm.txt";
	auto openedSeq = fileReader::ReadFile<aaSequence>(file);
	double weight = 0.0;
	for (auto &sequence: openedSeq){
		weight += sequence->weightCnt();
	}
	std::cout << std::fixed << std::setprecision(5) << weight << '\n';
}

//TODO TRIM INPUT SEQ
void Solution::FindProtMotiff(){

	/* Problem:
	https://rosalind.info/problems/mprt/
	*/
	std::string file = "data/rosalind_mprt.txt";
	auto protIDS = fileReader::simpleRead(file);
	std::string url = "http://www.uniprot.org/uniprot/";

	std::istringstream stream(*protIDS);
	std::string curID;

	std::vector<std::unique_ptr<aaSequence>> sequences;

	Request proteinFetch(url); 

	while(std::getline(stream, curID)){
		if (curID.empty()) continue;
		auto responseTmp = proteinFetch.fetchFasta(curID);

		if (!responseTmp){
			std::cerr << "Fetching fasta failed for: " << curID << std::endl;
			continue;
		}
		std::string response = std::move(*responseTmp);
		sequences = fileReader::ReadFromString<aaSequence>(std::move(response));

		for (auto &seq: sequences){
			auto indexes = seq->NGlyMotiff();
			if (!indexes.empty()){
				std::cout << seq->getID() << std::endl; 
				for (size_t i: indexes){
					std::cout << i << " "; 
				}
				std::cout << '\n';
			}
		}
	}
}

void Solution::cutIntrons(){

	/* Problem:
	https://rosalind.info/problems/splc/
	*/
	std::string file = "./data/rosalind_splc.txt";

	auto openedSeq = fileReader::ReadFile<DNA>(file);

	std::vector<std::unique_ptr<NtSequence>> transIntrons;
	for (auto &seq: openedSeq){
		if (auto *p = dynamic_cast<Transcriptable*>(seq.get())){
			std::unique_ptr<RNA> rna = p->transcribe();
			transIntrons.push_back(std::move(rna));
		}else
			std::cerr << "Input is not transcriptable" << std::endl;
	}
	std::unique_ptr<NtSequence> sequence = std::move(transIntrons.front());
	transIntrons.erase(transIntrons.begin());
	auto semiResult = sequence->cutIntrons(transIntrons);

	if (auto *p = dynamic_cast<Translatable*>(semiResult.get())){
		auto protein = p->translate();
		std::cout << protein->getSeq() << std::endl;
	}else
		std::cerr << "Could not translate the sequence" << std::endl;
}
