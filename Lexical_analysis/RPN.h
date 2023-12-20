#ifndef RPN_H
#define RPN_H

#include "../Error_handler/Error.h"
#include "IT.h"
#include "LT.h"
#include "../Meta/Meta_fst.h"
#include "../Meta/Meta_helper.h"
#include "Graph.h"

#include <iostream>
#include <algorithm>
#include <map>
#include <stack>
#include <string>
#include <vector>
#include <cmath>
#include <unordered_set>
#include <stdexcept>
#include <cassert>
#include <atomic>
#include <concepts>
#include <cstdint>
#include <regex>
#include <type_traits>
#include <functional>

#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>
#include <boost/algorithm/string/regex.hpp>
#include <boost/filesystem.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/dll/import.hpp>
#include <boost/function.hpp>
#include <boost/dll.hpp>
#include <boost/process.hpp>
#include <boost/type_index.hpp>

using namespace IT;

namespace RPN
{
	struct Function 
	{
	    std::string name;
	    std::string returnType;
	    std::vector<std::pair<int, std::string>> arguments;
	    std::string actionDescription;
	};

	bool isHexNumber(const std::string& number);
	bool isBinaryNumber(const std::string& word);

	void transformFromHex(std::string& word, std::string& line, const int& str_number, const int& pos);
	void transformFromBinary(std::string& word, std::string& line);

	class RPN_Creator
	{
		std::unordered_set<char> operators { '+', '-', '*', '/', '^', '#', '$', ':', '!', '>', '<', '&', '~', '=', '.', ',', '?', '='};
		std::unordered_set<char> symbols { ')', '(', ';', '#', '$', ':', '!', '>', '<', '&', '~' };

		std::stack<std::pair<std::string, char>> removedBrackets;

		std::string word;

		size_t start;

		std::stack<char> oper_stack;
		std::stack<double> val_stack;	

		std::map<std::string, double (*)(double, double)> ops {
		    {"+", [](double a, double b) { return a + b; }},
		    {"-", [](double a, double b) { return a - b; }},
		    {"*", [](double a, double b) { return a * b; }},
		    {"/", [](double a, double b) { if(b == 0) throw ERROR_THROW(613); return a / b; }},
		    {"^", [](double a, double b) { return pow(a, b); }},
		    {"%", [](double a, double b) { return fmod(a, b); }},
		    {"#", [](double a, double b) { if(a == 0) throw ERROR_THROW(614); return static_cast<double>(static_cast<int>(a) << static_cast<int>(b)); }},
		    {"$", [](double a, double b) { return static_cast<double>(static_cast<int>(a) >> static_cast<int>(b)); }},
		    {"&", [](double a, double b) { return static_cast<double>(static_cast<int>(a) & static_cast<int>(b)); }},
		    {"~", [](double a, double b) { return static_cast<double>(static_cast<int>(a) | static_cast<int>(b)); }},
		    {":", [](double a, double b) { return static_cast<double>(static_cast<int>(a) <= static_cast<int>(b)); }},
		    {"?", [](double a, double b) { return static_cast<double>(static_cast<int>(a) >= static_cast<int>(b)); }},
		    {"@", [](double a, double b) { return static_cast<double>(static_cast<int>(a) == static_cast<int>(b)); }},
		    {"!", [](double a, double b) { return static_cast<double>(static_cast<int>(a) != static_cast<int>(b)); }},
		    {">", [](double a, double b) { return static_cast<double>(static_cast<int>(a) > static_cast<int>(b)); }},
		    {"<", [](double a, double b) { return static_cast<double>(static_cast<int>(a) < static_cast<int>(b)); }}
		};

		std::map<std::string, std::string> sign{
			{"input", "int()"},
			{"factorial", "int(int)"},
			{"fibonacci", "int(int)"}
		};

		int precedence(char op);

		template <std::convertible_to<std::string> T>
		void replaceSubstring(std::string& line, const T& substr, const std::string& replacement) {
		    size_t pos = 0;

		    while ((pos = line.find(substr, pos)) != std::string::npos) {
		        line.replace(pos, std::char_traits<char>::length(substr), replacement);
		        pos += replacement.length();
		    }
		}

	public:
		void CheckLibFunctionCall(std::string& line, std::stack<std::pair<std::string, char>> brackets, const int& str_number, const int& pos, std::string& word, IdTable& idTable);
		void replaceFunctionCall(std::string& line, const int& str_number, const int& pos, const std::string& func_name, std::stack<std::pair<std::string, char>> brackets, const Function& function, const IdTable& idTable);
		void transform(std::string& line, std::stack<std::pair<std::string, char>> brackets, const int& type, const int& pos, const int& str_number, LT::LexTable& lexTable, IdTable& idTable);

		void get_polish_value(const std::string& line);

		std::vector<Function> functions;

		std::vector<std::string> library_paths{
			"/home/bararide/code_folder/Cpp/Genom/build/library"
		};

		std::vector<std::pair<boost::dll::shared_library, std::string>> libraries;
	};
}

#endif