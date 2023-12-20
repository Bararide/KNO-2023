#include "Lexical_analysis.h"

namespace LA
{
	template <typename T>
	concept Printable = requires(T t) {
	    { boost::lexical_cast<std::string>(t) };
	};

	typedef void (*FunctionType)(int);

	void Analysis::AnalysisImport(std::string& line, const int& str_number, LT::LexTable& lexTable, IT::IdTable& idTable)
	{
		std::regex pattern("import\\s+\"([^\"]+)\"");
		std::smatch match;
		boost::filesystem::path fullPath;
		bool its_find = false;

		if(std::regex_search(line, match, pattern))
		{
			std::string libName = match[1].str();
			libName += ".so";

			for(const std::string& path : polish_notation.library_paths)
			{
				fullPath = boost::filesystem::path(path) / (libName);
				if(boost::filesystem::exists(fullPath))
				{
					its_find = true;
					break;
				}
			}

			if(its_find)
			{
				boost::dll::shared_library library(fullPath.string());
				polish_notation.libraries.push_back({library, fullPath.string()});
			}
			else throw ERROR_THROW_IN(628, str_number, 0);
		}
		else throw ERROR_THROW_IN(627, str_number, 0);
	}

	bool Analysis::CheckCallFunction(std::string& line, const int& str_number, const int& pos, LT::LexTable& lexTable, IT::IdTable& idTable)
	{
	    boost::regex pattern(R"((\w+)\s+(\w+)\s*:\s*(\w+)\((.*?)\);)");
	    boost::smatch match;
	    int var_count = 0;

	    if (boost::regex_match(line, match, pattern)) 
	    {
	        std::string returnType = match[1].str();
	        std::string variableName = match[2].str();
	        std::string functionName = match[3].str();
	        std::string arguments = match[4].str();

	        auto func = std::find_if(polish_notation.functions.begin(), polish_notation.functions.end(), [functionName](const auto& v)
	        {
	        	//std::cout << v.name << '\t' << functionName << std::endl;
	        	return v.name == functionName;
	        });
	        if(func != polish_notation.functions.end())
	        {
		        std::regex argumentRegex(R"(\s*,\s*)");
		        std::sregex_token_iterator iter(arguments.begin(), arguments.end(), argumentRegex, -1);
		        std::sregex_token_iterator endIter;

		        int argumentIndex = 1;
		        while (iter != endIter) 
		        {
		        	auto var = std::find_if(idTable.table.begin(), idTable.table.end(), [v = *iter](const auto& e){
		        		return e.id == v && e.idtype == static_cast<IDTYPE>(4);
		        	});
		        	if(var == idTable.table.end()) throw ERROR_THROW_IN(611, str_number, pos);
		        	*iter++;
		        	var_count++;
		        }
		        if(var_count != func->arguments.size())
		        	throw ERROR_THROW_IN(619, str_number, pos);	        	
	        }
	        else throw ERROR_THROW_IN(621, str_number, pos);

	        its_function_call = true;

	        return true;
	    } 
	    else 
	    {
	        return false;
	    }
	}

	void Analysis::AnalysisCallFunction(std::string& line, const int& str_number, const int& pos, LT::LexTable& lexTable, IT::IdTable& idTable)
	{
		RPN::Function function;

		std::regex functionRegex(R"(^([a-zA-Z_][a-zA-Z0-9_]*)\[(.*?)\]\s+([a-zA-Z_][a-zA-Z0-9_]*)\((.*?)\))");

	    std::smatch match;
	    if (std::regex_match(line, match, functionRegex)) 
	    {
	        std::string returnType = match[2].str();
	        std::string functionName = match[3].str();
	        std::string argumentsStr = match[4].str();

	        function.name = functionName;
	        function.returnType = returnType;

	        std::regex argumentRegex(R"(\s*,\s*)");
	        std::sregex_token_iterator iter(argumentsStr.begin(), argumentsStr.end(), argumentRegex, -1);
	        std::sregex_token_iterator endIter;

	        int argumentIndex = 1;
	        while (iter != endIter) 
	        {
	            std::string argument = *iter++;
	            function.arguments.emplace_back(argumentIndex++, argument);
	        }

		    polish_notation.functions.push_back(function);
			if (std::count_if(polish_notation.functions.begin(), polish_notation.functions.end(), [](const auto& v) {
			        return v.name == std::string("main");
			    }) > 1) {
			    throw ERROR_THROW_IN(621, str_number, pos);
			}
	    }
	}

	bool Analysis::AnalysisFunctionBlock(std::string& line, int& pos, const int& str_number, LT::LexTable& lexTable, IT::IdTable& idTable)
	{
	    RPN::Function function;

	    std::regex regex(R"(\s*(\w+)\[([\w:]+)\]\s+(\w+)\((.*)\)\s*=>\s*(.*);\s*)");

	    std::smatch match;
	    if (std::regex_match(line, match, regex)) 
	    {
	        function.name = match[3].str();
	        function.returnType = match[2].str();
	        function.actionDescription = match[5].str();

	        std::string argumentsStr = match[4].str();
	        std::regex argumentsRegex(R"(\s*\[([\w:]+)\]\s+(\w+)\s*)");
	        std::smatch argumentsMatch;

	        auto argumentsBegin = argumentsStr.cbegin();
	        auto argumentsEnd = argumentsStr.cend();
	        while (std::regex_search(argumentsBegin, argumentsEnd, argumentsMatch, argumentsRegex)) 
	        {
	            if (argumentsMatch.size() == 3) 
	            {
	            	std::string type = argumentsMatch[1].str();
	            	int argumentType = 0;
	            	if(FST::execute<INTEGER>(type) && type.size() == INTEGER::states)
	            		argumentType = 1;
	            	else if(FST::execute<STRING>(type) && type.size() == STRING::states)
	            		argumentType = 2;
	            	else if(FST::execute<BOOLEAN>(type) && type.size() == BOOLEAN::states)
	            		argumentType = 4;
	            	else if(FST::execute<ONEBYTE>(type) && type.size() == ONEBYTE::states)
	            		argumentType = 5;
	            	else throw ERROR_THROW(618);
	                std::string argumentName = argumentsMatch[2].str();
	                function.arguments.emplace_back(argumentType, argumentName);
	            }
	            argumentsBegin = argumentsMatch[0].second;
	        }
	    }
	    else return false;
	    polish_notation.functions.push_back(function);
			if (std::count_if(polish_notation.functions.begin(), polish_notation.functions.end(), [](const auto& v) {
			        return v.name == std::string("main");
			    }) > 1) {
			    throw ERROR_THROW(621);
			}

	    // std::cout << "Function Name: " << function.name << std::endl;
	    // std::cout << "Return Type: " << function.returnType << std::endl;
	    // std::cout << "Arguments: " << std::endl;
	    // for (const auto& argument : function.arguments) {
	    //     std::cout << "- Type: " << argument.first << ", Name: " << argument.second << std::endl;
	    // }
	    // std::cout << "Action Description: " << function.actionDescription << std::endl;
	    return true;
	}

	bool Analysis::AnalysisBlock(std::string& line, int& pos, const int& str_number, LT::LexTable& lexTable, IT::IdTable& idTable)
	{
	    if(line.find("=>") != std::string::npos && line.find('{') != std::string::npos)
	    {
	        throw ERROR_THROW(609);
	    }

	    start = line.find('(');
	    end = line.rfind(')', line.find("=>"));
	    if(start == std::string::npos || end == std::string::npos) return false;

	    std::string expr = line.substr(start + 1, end - start - 1);
	    expr.insert(expr.begin(), ' ');
	    expr.insert(expr.begin(), '=');
	    //std::cout << "expr " << expr << std::endl;
	    std::istringstream iss(expr);

	    std::string word;
	    std::size_t operatorPos = expr.find("=>");

	    while(iss >> word)
	    {
	        boost::regex pattern("\\b(\\w+)");
	        boost::smatch match;

	        if (boost::regex_search(word, match, pattern)) 
	        {
	            word = match[1];
	            //std::cout << word << std::endl;
	            if(FST::execute<RANDOM>(word) && word.size() == RANDOM::states)
	            {
	                //std::cout << word << std::endl;
	                its_lib_function = true;
	            }
	            else if(FST::execute<FACTORIAL>(word) && word.size() == FACTORIAL::states)
	            {
	                its_lib_function = true;
	            }
	        }

	        if (operatorPos != std::string::npos && iss.tellg() > static_cast<std::streampos>(operatorPos))
	        {
	            break;
	        }
	    }

	    if(its_lib_function)
	    {
	    	if(expr.find_first_of(arithmetic_symbols) != std::string::npos) throw ERROR_THROW(625);
	        expr.clear();
	        its_lib_function = false;
	        return false;
	    }
	    polish_notation.transform(expr, brackets, 5, 0, str_number, lexTable, idTable);

	    expr.erase(expr.begin());
	    expr.pop_back();

	    line.replace(start + 1, end - start - 1, expr);
	    if(line.find("=>") != std::string::npos) {AnalysisShortConstr(line); pos = -1;}
	    else {lexTable.table.push_back({LEX_IF, str_number, LT_TI_NULLXDX}); its_if_construction = true;}
	    return true;
	}

	void Analysis::AnalysisShortConstr(std::string& line)
	{
	    start = line.find('(');
	    end = line.find(')');
	    arrowPos = line.find("=>", end + 1);

	    bool expr_result = 0;

	    if (start == std::string::npos || end == std::string::npos || start >= end)
	    {
	        std::string result = line.substr(arrowPos + 2);
	    	boost::trim(result);
	    	return;
	    }

	    std::string expression = line.substr(start + 1, end - start - 1);
	    boost::trim(expression);

	    if(boost::lexical_cast<bool>(expression) == false) line.clear();
	    else
	    {
		    std::string result = line.substr(arrowPos + 2);
		    boost::trim(result);
		    line = result;
	    }
	}
}