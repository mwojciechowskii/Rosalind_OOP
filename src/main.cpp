#include "Solution.hpp"
#include "ArgParser.hpp"
#include <cstdio>
#include <curl/curl.h>
#include <iostream>

using namespace std;

size_t chooseSolution(){

	cout << "Choose Rosalind solution to see: " << endl;

	for (size_t i = 0; i < Solution::methods.size(); i++) {
        cout << (i + 1) << ") " << Solution::methods[i] << std::endl;
    }
	size_t option;
	cin >> option;
	return option;
}

void printSolution(size_t &option){

	if (option < Solution::methods.size()){
		const std::vector<void(*)()> actions = {
        Solution::HammingDist,
        Solution::GCcount,
        Solution::FindMotiff,
        Solution::RabbitsRec,
        Solution::MendelLaw,
        Solution::Translation,
        Solution::CalcProteinMass,
        Solution::FindProtMotiff,
        Solution::cutIntrons
    };
		std::cout << Solution::methods[option] << " solution: " << std::endl;
		actions[option -1]();
	}else cerr << "Wrong input number";

}

int main(int argc, char** argv){

	ArgParser argparse("Rosalind solutions", "Allows to see my rosalind progress", true);
	argparse.addArgument("Default", "d", "default", "allows to run program with predefined inputs");
	argparse.addArgument("First file", "i", "", "first input file to be provided");
	argparse.addArgument("Second file", "I", "", "second input file to be provided");

	argparse.parseArgs(argc, argv);

	if (argparse.isPresent("Default")){
		auto var = chooseSolution();
		printSolution(var);
	}

	return 0;
}
