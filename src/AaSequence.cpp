#include "aminoAcidsWeight.hpp"
#include "AaSequence.hpp"
#include <unordered_map>

double aaSequence::weightCnt(){

	double Weight = 0.0;
	for (char &chunk: Seq){
		std::unordered_map<char, double>::const_iterator singleWeight = WEIGHTS_AA.find(chunk);
		if (singleWeight == WEIGHTS_AA.end())
			continue;
		else Weight += singleWeight->second;
	}
	return Weight;
}

