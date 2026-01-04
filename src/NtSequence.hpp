#pragma once
#include "Sequence.hpp"
#include <memory>
#include <optional>
#include <string>
#include <vector>

class NtSequence: public Sequence {
protected:
	static bool CompareGC(const std::unique_ptr<NtSequence>& seqA, const std::unique_ptr<NtSequence>& seqB) {return seqA->GCcontent() < seqB->GCcontent();}
	virtual std::unique_ptr<NtSequence> makeRes(std::string &seq_id, std::string &id_info, std::string &sequence) const = 0;

public:
	using Sequence::Sequence;
	using BaseType = NtSequence;

	struct NtAmount{
		std::size_t a{0}, c{0}, g{0};
		std::optional<std::size_t> t{}; 
		std::optional<std::size_t> u{};
	};
	mutable NtAmount ntAmount;
	mutable bool NtCounted = false;
	NtAmount CntNt() const;
	virtual std::string Complement();
	float GCcontent() const;
	size_t HammingDist(const NtSequence& other);
	std::vector<size_t> FindMotiff(const std::string& motif) const;
	std::vector<size_t> FindMotiff(const NtSequence& motif) const;

	static const NtSequence* HighestGC(const std::vector<std::unique_ptr<NtSequence>>& sequences);

	std::string parseIntron(const std::string &intron, std::string cutSeq);
	std::unique_ptr<NtSequence> cutIntrons(const std::vector<std::unique_ptr<NtSequence>> &introns);

};
