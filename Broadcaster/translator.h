#ifndef ASM_H
#define ASM_H

#include "../Lexical_analysis/LT.h"
#include "../Lexical_analysis/IT.h"

#include <string>
#include <fstream>
#include <memory>
#include <type_traits>
#include <algorithm>
#include <stack>

#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>

#define INCL   "extern printf\nextern write\n"
#define DATA   "section .data\n"
#define BSS    "section .bss\n\tbool resb 1\n\tubyte resw 1\n\tresint resd 1\n\tresstr resq 1\n\n"
#define START  "section .text\n\tglobal main\n"
#define END    "\n\tmov eax, 60\n\txor edi, edi\n\tsyscall"
#define FORMAT "\tformat db \"%d\", 10, 0\n\tfmtstr db \"%s\", 10, 0\n\tfmtint db \"%ld\", 10, 0\n"

namespace ASM
{
	class Translator
	{
	private:
		std::string line;
		std::ofstream stream;

	public:
		Translator():stream("out.asm"){}

		void transform_data_generator(LT::LexTable& lexTable, IT::IdTable& idTable);
		void generator(LT::LexTable& lexTable, IT::IdTable& idTable);
	};
}

#endif