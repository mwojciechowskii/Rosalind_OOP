#pragma once

#include "RNA.hpp"
#include "NtSequence.hpp"
#include "interface/Transcriptable.hpp"
#include <string>

class DNA: public NtSequence, public Transcriptable{
	private:
	std::string RunTranscript() const;

public:
	using NtSequence::NtSequence;
	using BaseType = NtSequence;
	~DNA() = default;
	std::unique_ptr<RNA> transcribe() const override;
	Type getType() const override {return Type::DNA;}

};
