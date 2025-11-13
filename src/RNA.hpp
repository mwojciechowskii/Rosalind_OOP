#pragma once

#include "sequence.hpp"

class RNA: public Sequence{
public:
	using Sequence::Sequence;
	~RNA() = default;
	NtAmount CntNt() override;	

};
