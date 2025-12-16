#include "RNA.hpp"
#include "resources/codonTable.hpp"
#include "AaSequence.hpp"
#include <memory>

std::string RNA::RunTranslation() const{

	std::string seqAA;
	for (std::size_t i = 0; i < Seq.length(); i += 3) {
		std::string chunk = Seq.substr(i, 3);

		std::unordered_map<std::string, char>::const_iterator aminoAcid = CODON_TABLE.find(chunk);
		if (aminoAcid == CODON_TABLE.end())
			continue;
		if (aminoAcid->second == '*') 
			break;
		else seqAA.push_back(aminoAcid->second);
	}   
	return seqAA;
}

std::unique_ptr<aaSequence> RNA::translate() const{

	std::string aaSeq = RunTranslation();
	std::string id_copy = Seq_ID;
	std::string id_info_copy = ID_info + "_Translated";
	return std::make_unique<aaSequence>(std::move(id_copy), std::move(id_info_copy), std::move(aaSeq));
}

