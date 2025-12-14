#pragma once
#include "Sequence.hpp"

class aaSequence: public Sequence {

public:
	using Sequence::Sequence;
	using BaseType = aaSequence;

    Type getType() const override {return Type::AAseq;}
	double weightCnt();
};
