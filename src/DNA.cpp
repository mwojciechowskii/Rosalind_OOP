#include "DNA.hpp"
#include <RNA.hpp>
#include <string>

std::string DNA::RunTranscript(){

	std::string Rna;
	
	for (char nt: Seq){
		switch (nt) {
			default:
				break;
			case 'a': case 'A':
				Rna.push_back('A');
				break;
			case 't': case 'T':
				Rna.push_back('U');
				break;
			case 'c': case 'C':
				Rna.push_back('C');
				break;
			case 'g': case 'G':
				Rna.push_back('G');
				break;
		}
	}
	return Rna;
}

RNA DNA::Transcribe(){
	std::string RnaSeq = RunTranscript();
	return RNA(RnaSeq);
}


