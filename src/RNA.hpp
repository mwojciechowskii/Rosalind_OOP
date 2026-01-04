#pragma once

#include "NtSequence.hpp"
#include "interface/Translatable.hpp"
#include <string>

class RNA: public NtSequence, public Translatable{
private:
	std::string RunTranslation() const;

	std::unique_ptr<NtSequence> makeRes(std::string &seq_id, std::string &id_info, std::string &sequence) const override{
		return std::make_unique<RNA>(std::move(seq_id), std::move(id_info), std::move(sequence));}
public:
	using NtSequence::NtSequence;
	~RNA() = default;
	using BaseType = NtSequence;
	Type getType() const override {return Type::RNA;}
	std::unique_ptr<aaSequence> translate() const override;
};
