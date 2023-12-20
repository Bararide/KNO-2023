#ifndef LEXICAL_ANALYSIS_H
#define LEXICAL_ANALYSIS_H

#define SPACE ' '
#define SEPARATOR '|'
#define LINE_FEED '\n'
#define token_size 256

#include "../Main/In.h"
#include "../Meta/Meta_fst.h"
#include "../Meta/Meta_helper.h"
#include "Graph.h"
#include "LT.h"
#include "IT.h"
#include "RPN.h"

#include <algorithm>
#include <string_view>
#include <stack>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <atomic>
#include <memory>
#include <concepts>
#include <limits>
#include <vector>
#include <regex>

#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string/find.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>

using namespace IT;

namespace LA
{
	struct TypeOfVar
	{
		int LT_position = -1;
		enum { DEF = 0, INT = 1, STR = 2, FUN = 3, BOOL = 4, BYTE = 5, ARG = 6} type = DEF;
	};

	class Analysis
	{
	private:
		std::string line;
		std::string_view symbols = ",.;:(){}[]=-+*/><";
		std::string_view arithmetic_symbols  = "-+*/><!~&";
		std::string last_id;
		TypeOfVar type_of_flag;

		bool its_string_literal     = false;
		bool its_function_param     = false;
		bool its_if_construction    = false;
		bool its_function           = false;
		bool its_lambda             = false;
		bool its_lib_function       = false;
		bool its_call               = false;
		bool its_function_call      = false;

		size_t start;
		size_t end;
		size_t arrowPos;

		int type;

		RPN::RPN_Creator polish_notation;

		std::stack<std::pair<std::string, char>> brackets;
		std::stack<std::pair<std::string, char>> removedBrackets;
		std::vector<std::pair<std::string, std::vector<std::string>>> id_vision;

		bool AnalyseIdentificator(std::string token, const int& str_number, const int& pos, LT::LexTable& lexTable, IT::IdTable& idTable);
		bool AnalysisWord(std::string word, std::string& line, int& pos, const int& str_number, LT::LexTable& lexTable, IT::IdTable& idTable);
		bool AnalysisSymbol(char token, std::string& line, int str_number, int pos, LT::LexTable& lexTable, IT::IdTable& idTable);
		bool AnalysisFunctionBlock(std::string& line, int& pos, const int& str_number, LT::LexTable& lexTable, IT::IdTable& idTable);
		bool AnalysisBlock(std::string& line, int& pos, const int& str_number, LT::LexTable& lexTable, IT::IdTable& idTable);

		bool CheckCallFunction(std::string& line, const int& str_number, const int& pos, LT::LexTable& lexTable, IT::IdTable& idTable);

		void AnalysisImport(std::string& line, const int& str_number, LT::LexTable& lexTable, IT::IdTable& idTable);
		void AnalysisLine(std::string& line, int str_number, LT::LexTable& lexTable, IT::IdTable& idTable);
		void AnalysisShortConstr(std::string& line);
		void AnalysisCallFunction(std::string& line, const int& str_number, const int& pos, LT::LexTable& lexTable, IT::IdTable& idTable);
		void Clear();

	public:

		Analysis(){ brackets.push({"glob", '{'}); id_vision.reserve(50); }
		void FindLex(const In::IN& source, LT::LexTable& lexTable, IT::IdTable& idTable);
	};
}

#endif