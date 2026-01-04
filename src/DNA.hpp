#pragma once

#include "RNA.hpp"
#include "NtSequence.hpp"
#include "interface/Transcriptable.hpp"
#include <string>

class DNA: public NtSequence, public Transcriptable{
	private:
	std::string RunTranscript() const;

	std::unique_ptr<NtSequence> makeRes(std::string &seq_id, std::string &id_info, std::string &sequence) const override{
		return std::make_unique<DNA>(std::move(seq_id), std::move(id_info), std::move(sequence)); }
public:
	using NtSequence::NtSequence;
	using BaseType = NtSequence;
	~DNA() = default;
	std::unique_ptr<RNA> transcribe() const override;
	Type getType() const override {return Type::DNA;}
	
};
