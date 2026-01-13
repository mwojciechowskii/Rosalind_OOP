#pragma once

#include <string>
#include <vector>
#include <ctime>

class Solution {
private:
	static double MendelHelper(double allele);

public:
	static void HammingDist();
	static void GCcount();
	static void FindMotiff();

	static void RabbitsRec();
	static void MendelLaw();
	static void Translation();
	static void CalcProteinMass();
	static void FindProtMotiff();
	static void cutIntrons();

	inline static const std::vector<std::string> methods = {"HammingDist",
		"GCcount",
		"FindMotiff", 
		"RabbitsRec", 
		"MendelLaw",
		"Translation",
		"CalcProteinMass", 
		"FindProtMotiff", 
		"cutIntrons",
	};
};
