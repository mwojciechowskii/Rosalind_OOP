#pragma once
#include <cstddef>
#include <optional>
#include <string>

class Sequence{

	protected:
		static std::string file_read(const std::string &file);
		std::string Seq;
	public:

		Sequence(const std::string &file);
		virtual ~Sequence() = default;
		const std::string& seq() { return Seq; }

		struct NtAmount{
			std::size_t a{0}, c{0}, g{0};
		    std::optional<std::size_t> t{}; 
			std::optional<std::size_t> u{};
		};
		NtAmount ntAmount;
		virtual NtAmount CntNt();
		std::string ComplementDNA();
};
