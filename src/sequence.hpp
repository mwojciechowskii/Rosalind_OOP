#pragma once
#include <algorithm>
#include <cstddef>
#include <memory>
#include <optional>
#include <string>
#include <vector>

class Sequence{

	protected:
		static std::string file_read(const std::string &file);
		std::string Seq_ID;
		std::string ID_info;
		std::string Seq;
		template<class SeqType>
		static bool CompareGC(const std::unique_ptr<SeqType>& seqA, const std::unique_ptr<SeqType>& seqB) {return seqA->GCcontent() < seqB->GCcontent();}

	public:

		Sequence(const std::string &file): Seq(file_read(file)) {}
		Sequence(const std::string &&seq_id, std::string &&sequence) : Seq_ID(std::move(seq_id)), Seq(std::move(sequence)) {};
		Sequence(const std::string &&seq_id, std::string &&id_info, std::string &&sequence) : Seq_ID(std::move(seq_id)), ID_info(std::move(id_info)), Seq(std::move(sequence)) {};
		virtual ~Sequence() = default;
		const std::string& seq() const { return Seq; }
		const std::string& id() const { return Seq_ID; }
		const std::string& id_info() const { return ID_info; }

		struct NtAmount{
			std::size_t a{0}, c{0}, g{0};
		    std::optional<std::size_t> t{}; 
			std::optional<std::size_t> u{};
		};
		NtAmount ntAmount;
		virtual NtAmount CntNt();
		virtual std::string Complement();
		float GCcontent() const;
		size_t HammingDist(const Sequence& other);
		//template<typename SeqType>
		//static SeqType* HighestGC(const std::vector<std::unique_ptr<SeqType>>& sequences);
		
		template<typename SeqType>
		static const SeqType* HighestGC(const std::vector<std::unique_ptr<SeqType>>& sequences){
			if(sequences.empty())
				return nullptr;
			auto maxGCval = std::max_element(sequences.begin(), sequences.end(), CompareGC<SeqType>);
			return maxGCval->get();
		}
};
