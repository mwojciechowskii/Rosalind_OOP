#pragma once

#include <sequence.hpp>

class RNA: protected Sequence{
public:
	using Sequence::Sequence;
	~RNA();
	NtAmount CntNt() override;	

};
