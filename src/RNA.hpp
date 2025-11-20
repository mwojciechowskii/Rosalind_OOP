#pragma once

#include "NtSequence.hpp"

class RNA: public NtSequence{
public:
	using NtSequence::NtSequence;
	~RNA() = default;
	Type getType() const override {return Type::RNA;}
};
