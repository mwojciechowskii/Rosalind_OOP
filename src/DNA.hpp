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
	std::unique_ptr<RNA> Transcribe();
	Type getType() const override {return Type::DNA;}

};
