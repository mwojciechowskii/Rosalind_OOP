#pragma once
#include <string>

class Sequence{

	protected:
		std::string Seq_ID;
		std::string ID_info;
		std::string Seq;

	public:

		Sequence(std::string &&sequence): Seq(sequence) {}; 
		//Sequence(std::string &sequence): Seq(sequence) {}; 
		Sequence(std::string &&seq_id, std::string &&sequence) : Seq_ID(std::move(seq_id)), Seq(std::move(sequence)) {};
		Sequence(std::string &&seq_id, std::string &&id_info, std::string &&sequence) : Seq_ID(std::move(seq_id)), ID_info(std::move(id_info)), Seq(std::move(sequence)) {};
		virtual ~Sequence() = default;
		const std::string& get_seq() const {return Seq;}
		const std::string& get_id() const {return Seq_ID;}
		const std::string& get_idInfo() const {return ID_info;}
		enum class Type {DNA, RNA, AAseq};
		virtual Type getType() const = 0;
};
