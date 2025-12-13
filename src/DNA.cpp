#include "DNA.hpp"
#include "RNA.hpp"
#include <memory>
#include <string>


std::string DNA::RunTranscript() {

	std::string Rna;

	for (char nt : Seq) {
		switch (nt) {
			default:
				break;
			case 'a':
			case 'A':
				Rna.push_back('A');
				break;
			case 't':
			case 'T':
				Rna.push_back('U');
				break;
			case 'c':
			case 'C':
				Rna.push_back('C');
				break;
			case 'g':
			case 'G':
				Rna.push_back('G');
				break;
		}
	}
	return Rna;
}

std::unique_ptr<RNA> DNA::Transcribe(){
	std::string RnaSeq = RunTranscript();
	std::string id_copy = Seq_ID;
	std::string id_info_copy = ID_info + "_Transcribed";
	return std::make_unique<RNA>(std::move(id_copy), std::move(id_info_copy), std::move(RnaSeq));
}
