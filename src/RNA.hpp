#pragma once

#include "sequence.hpp"

class RNA: public Sequence{
public:
	using Sequence::Sequence;
	~RNA() = default;
	Type getType() const override {return Type::RNA;}
};
