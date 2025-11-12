#pragma once

#include "sequence.hpp"

class RNA: protected Sequence{
public:
	using Sequence::Sequence;
	~RNA() = default;
	NtAmount CntNt() override;	

};
