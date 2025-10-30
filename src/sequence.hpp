#pragma once
#include <string>

class Sequence{

	protected:
		static std::string file_read(const std::string &file);
	public:

		std::string Seq;
		Sequence(const std::string &file);

		struct NtAmount{
			unsigned a;
			unsigned t;
			unsigned g;
			unsigned c;
		};
		NtAmount CntNt();
		void PrintStatistics(const Sequence::NtAmount &ntamount);
		std::string Transcribe();
		void PrintRNA(std::string RNAseq);
};
