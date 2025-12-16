#pragma once

#include "NtSequence.hpp"
#include "interface/Translatable.hpp"
#include <string>

class RNA: public NtSequence, public Translatable{
private:
	std::string RunTranslation() const;
public:
	using NtSequence::NtSequence;
	~RNA() = default;
	using BaseType = NtSequence;
	Type getType() const override {return Type::RNA;}
	std::unique_ptr<aaSequence> translate() const override;

};
