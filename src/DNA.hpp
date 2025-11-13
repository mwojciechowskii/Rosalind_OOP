#pragma once

#include "sequence.hpp"
#include "RNA.hpp"
#include <string>

class DNA: public Sequence{
	private:
	std::string RunTranscript();

public:
	using Sequence::Sequence;
	~DNA() = default;
	RNA Transcribe();

};
