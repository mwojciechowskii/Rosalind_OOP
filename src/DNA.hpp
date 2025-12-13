#pragma once

#include "RNA.hpp"
#include "NtSequence.hpp"
#include <string>

class DNA: public NtSequence{
	private:
	std::string RunTranscript();

public:
	using NtSequence::NtSequence;
	using BaseType = NtSequence;
	~DNA() = default;
	std::unique_ptr<RNA> Transcribe();
	Type getType() const override {return Type::DNA;}

	virtual std::unique_ptr<aaSequence> Translate() override {return nullptr;}
};
