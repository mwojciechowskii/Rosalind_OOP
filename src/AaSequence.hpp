#pragma once
#include "Sequence.hpp"
#include <vector>

class aaSequence: public Sequence {

public:
	using Sequence::Sequence;
	using BaseType = aaSequence;

    Type getType() const override {return Type::AAseq;}
	double weightCnt();
	std::vector<size_t> NGlyMotiff();
};
