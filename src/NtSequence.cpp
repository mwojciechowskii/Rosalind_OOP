#include "NtSequence.hpp"
#include <algorithm>
#include <iostream>

NtSequence::NtAmount NtSequence::CntNt () const{

	if (NtCounted){
		return ntAmount;
	}

	Type seqType = getType();
	if (seqType == Type::DNA) {
		ntAmount.t = 0;
	} else if(seqType == Type::RNA){
		ntAmount.u = 0;
	}
	for (char Nt : Seq){
		switch (Nt){
			default:
				std::cerr << "Invalid nucleotide found: " << Nt << "in: " << Seq_ID << std::endl; break;
			case 'T': case 't' :
				++*ntAmount.t; break;
			case 'A': case 'a':
				++ntAmount.a; break;
			case 'G': case 'g':
				++ntAmount.g; break;
			case 'C': case 'c':
				++ntAmount.c; break;
		}
	}
	NtCounted = true;
	return ntAmount;
}

std::string NtSequence::Complement(){

	std::string CompSeq;
	for (char nt : Seq){

		switch (nt) {
			default:
			break;
			case 'A': case 'a':
				CompSeq.push_back('T');
				break;
			case 'T': case 't':
				CompSeq.push_back('A');
				break;
			case 'G': case 'g':
				CompSeq.push_back('C');
				break;
			case 'C': case 'c':
				CompSeq.push_back('G');
				break;
			}	
	}
	std::reverse(CompSeq.begin(), CompSeq.end());
	return CompSeq;
}

size_t NtSequence::HammingDist(const NtSequence& other){

	size_t len = std::min(Seq.size(), other.Seq.size());
	size_t dist = 0;
	for (size_t i =0; i < len; i++){
		dist += (Seq[i] != other.Seq[i]);
	}
	return dist;
}

float NtSequence::GCcontent () const{

	CntNt();
	std::size_t sum = ntAmount.a;
	std::size_t GCsum = ntAmount.c + ntAmount.g;
	if (ntAmount.t.has_value()){
		sum += *ntAmount.t;	
	} else if (ntAmount.u.has_value()){
		sum += *ntAmount.u;
	}
	sum += GCsum;
	return (static_cast<float>(GCsum)/sum) * 100.0f;
}

std::vector<size_t> NtSequence::FindMotiff(const std::string& motif) const{

	std::vector<size_t> MottifIndexes;
	if (motif.empty() || motif.length() > Seq.length())
		return MottifIndexes;
	
	size_t pos = 0;
	while ((pos = Seq.find(motif, pos)) != std::string::npos) {

		MottifIndexes.push_back(pos + 1);
		++pos;
	}
	return MottifIndexes;
}

std::vector<size_t> NtSequence::FindMotiff(const NtSequence& motif) const{
	return FindMotiff(motif.get_seq());
}

const NtSequence* NtSequence::HighestGC(const std::vector<std::unique_ptr<NtSequence>>& sequences){

	if(sequences.empty())
		return nullptr;
	auto maxGCval = std::max_element(sequences.begin(), sequences.end(), CompareGC);
	return maxGCval->get();
}

