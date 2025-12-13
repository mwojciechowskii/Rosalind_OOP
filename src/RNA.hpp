#pragma once

#include "NtSequence.hpp"
#include "AaSequence.hpp"
#include <string>

class RNA: public NtSequence{
private:
	std::string RunTranslation();
public:
	using NtSequence::NtSequence;
	~RNA() = default;
	using BaseType = NtSequence;
	Type getType() const override {return Type::RNA;}
	std::unique_ptr<aaSequence> Translate() override;
};
