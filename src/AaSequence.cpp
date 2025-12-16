#include "resources/aminoAcidsWeight.hpp"
#include "AaSequence.hpp"
#include <unordered_map>
#include <boost/regex.hpp>
#include <iterator>

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

std::vector<size_t> aaSequence::NGlyMotiff(){

	boost::regex re("(?=(N[^P][ST][^P]))");
	std::vector<size_t> indexes;

	auto index = Seq.cbegin();
    auto seqEnd = Seq.cend();

	while(index != seqEnd){
        boost::match_results<std::string::const_iterator> matchIT;
        if (!boost::regex_search(index, Seq.cend(), matchIT, re)) break;
        auto motifStartIt = matchIT[1].first;
        size_t pos = static_cast<size_t>(std::distance(Seq.cbegin(), motifStartIt));
        indexes.push_back(pos + 1);

        index = Seq.cbegin() + static_cast<std::ptrdiff_t>(pos + 1);
	}
	return indexes;
}

