#include "RNA.hpp"
#include <sequence.hpp>

Sequence::NtAmount RNA::CntNt(){

	ntAmount.u = 0;

	for (char &Nt : Seq){

		switch (Nt){
			default:
				break;
			case 'U': case 'u' :
				++*ntAmount.u;
				break;
			case 'A': case 'a':
				++ntAmount.a;
				break;
			case 'G': case 'g':
				++ntAmount.g;
				break;
			case 'C': case 'c':
				++ntAmount.c;
				break;
		}
	}
	return ntAmount;

}
