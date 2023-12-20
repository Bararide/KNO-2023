#include "Lexical_analysis.h"

namespace LA
{
	void Analysis::FindLex(const In::IN& source, LT::LexTable& lexTable, IT::IdTable& idTable)
	{
		source.text[strlen(reinterpret_cast<char*>(source.text))] = SEPARATOR;
		for (int i = 0, j = 0; i < strlen(reinterpret_cast<const char*>(source.text)); ++i)
		{
			if(source.text[i] != SEPARATOR)
			{
				line += source.text[i];
			}
			else if(source.text[i] == SEPARATOR || source.text[i] == LINE_FEED)
			{
				++j;
				AnalysisLine(line, j, lexTable, idTable);
				line.clear();
			}
		}

		id_vision.shrink_to_fit();
		idTable.table.shrink_to_fit();
	}

	void Analysis::AnalysisLine(std::string& line, int str_number, LT::LexTable& lexTable, IT::IdTable& idTable)
	{
		std::string word;
		type_of_flag.type = TypeOfVar::DEF;

		int i = 0;
		bool inside_literal = false;

		for(i = 0; i < line.size(); ++i)
		{
		    if (line.at(i) == LEX_EQUAL_SIGN && line.at(i + 1) == LEX_BIG)
		    {
		        std::string combinedStr = std::string(1, line.at(i)) + std::string(1, line.at(i + 1));
		        AnalysisWord(combinedStr, line, i, str_number, lexTable, idTable);
		        i += 2;
		    }

		    if (inside_literal)
		    {
		        if (line[i] == '\'')
		        {
		            inside_literal = false;
		        }
		        word += line[i];
		    }
		    else if (symbols.find(line[i]) == std::string::npos && line[i] != ' ')
		    {
		        if (line[i] == '\'')
		        {
		            if (std::count(line.begin(), line.end(), '\'') != 2)
		                throw ERROR_THROW_IN(127, str_number, i);
		            inside_literal = true;
		        }
		        word += line[i];
		    }
		    else if (!word.empty())
		    {
		        AnalysisWord(word, line, i, str_number, lexTable, idTable);
		        word.clear();
		    }

		    if (symbols.find(line[i]) != std::string::npos)
		    {
		        AnalysisSymbol(line[i], line, i, str_number, lexTable, idTable);
		    }
		}

		if (!word.empty())
		{
		    AnalysisWord(word, line, i, str_number, lexTable, idTable);
		}
		line.clear();
	}

	bool Analysis::AnalysisWord(std::string word, std::string& line, int& pos, const int& str_number, LT::LexTable& lexTable, IT::IdTable& idTable)
	{
		type_of_flag.LT_position = str_number;
		if(FST::execute<FUNCTION>(word) && word.size() == FUNCTION::states)
		{
			if(AnalysisFunctionBlock(line, pos, str_number, lexTable, idTable) == true)
				its_lambda = true;
			else {AnalysisCallFunction(line, str_number, pos, lexTable, idTable); its_function = true;}
			lexTable.table.push_back({LEX_FUNCTION, str_number, LT_TI_NULLXDX});
			return true;
		}
		else if(FST::execute<INTEGER>(word) && word.size() == INTEGER::states)
		{
			lexTable.table.push_back({LEX_TYPE, str_number, LT_TI_NULLXDX});
			type_of_flag.type = TypeOfVar::INT;
			return true;
		}
		else if(FST::execute<STRING>(word) && word.size() == STRING::states)
		{
			lexTable.table.push_back({LEX_TYPE, str_number, LT_TI_NULLXDX});
			type_of_flag.type = TypeOfVar::STR;		
			return true;
		}
		else if(FST::execute<RETURN>(word) && word.size() == RETURN::states)
		{
			lexTable.table.push_back({LEX_RETURN, str_number, LT_TI_NULLXDX});
			return true;
		}
		else if(FST::execute<IMPORT>(word) && word.size() == IMPORT::states)
		{
			lexTable.table.push_back({LEX_IMPORT, str_number, LT_TI_NULLXDX});
			AnalysisImport(line, str_number, lexTable, idTable);
			return true;
		}
		else if(FST::execute<BOOLEAN>(word) && word.size() == BOOLEAN::states)
		{
			lexTable.table.push_back({LEX_TYPE, str_number, LT_TI_NULLXDX});
			type_of_flag.type = TypeOfVar::BOOL;
			return true;	
		}
		else if(FST::execute<ONEBYTE>(word) && word.size() == ONEBYTE::states)
		{
			lexTable.table.push_back({LEX_TYPE, str_number, LT_TI_NULLXDX});
			type_of_flag.type = TypeOfVar::BYTE;
			return true;	
		}
		else if(FST::execute<RANDOM>(word) && word.size() == RANDOM::states)
		{
			lexTable.table.push_back({LEX_LIB, str_number, LT_TI_NULLXDX});
			return true;	
		}
		else if(FST::execute<SHORT_OPER>(word) && word.size() == SHORT_OPER::states)
		{
			lexTable.table.push_back({LEX_OPERATOR, str_number, LT_TI_NULLXDX});
			return true;
		}
		else if(FST::execute<TRUE>(word) && word.size() == TRUE::states)
		{
			lexTable.table.push_back({LEX_LITERAL, str_number, LT_TI_NULLXDX});
		    auto isIdTableEntry = [&](const auto& v) {
		        return v.id == last_id && v.idtype == 4;
		    };

		    auto idTableEntry = std::find_if(idTable.table.begin(), idTable.table.end(), isIdTableEntry);

		    if (idTableEntry == idTable.table.end())
		    {
		        if (type_of_flag.type == TypeOfVar::BOOL)
		        {
		            idTable.table.push_back({
		                const_cast<char*>(brackets.top().first.c_str()),
		                str_number,
		                const_cast<char*>(last_id.c_str()),
		                type_of_flag.type,
		                4,
		                1
		            });
		        }
		    }		    

			return true;
		}
		else if(FST::execute<FALSE>(word) && word.size() == FALSE::states)
		{
			lexTable.table.push_back({LEX_LITERAL, str_number, LT_TI_NULLXDX});

		    auto isIdTableEntry = [&](const auto& v) {
		        return v.id == last_id && v.idtype == 4;
		    };

		    auto idTableEntry = std::find_if(idTable.table.begin(), idTable.table.end(), isIdTableEntry);

		    if (idTableEntry == idTable.table.end())
		    {
		        if (type_of_flag.type == TypeOfVar::BOOL)
		        {
		            idTable.table.push_back({
		                const_cast<char*>(brackets.top().first.c_str()),
		                str_number,
		                const_cast<char*>(last_id.c_str()),
		                type_of_flag.type,
		                4,
		                0
		            });
		        }
		    }

			return true;
		}
		else if (FST::execute<STRING_LITERAL>(word))
		{
		    lexTable.table.push_back({LEX_LITERAL, str_number, LT_TI_NULLXDX});

		    auto isIdTableEntry = [&](const auto& v) {
		        return v.id == last_id && v.idtype == 1 && brackets.top().first == v.parrent_function;
		    };

		    auto idTableEntry = std::find_if(idTable.table.begin(), idTable.table.end(), isIdTableEntry);

		    if (idTableEntry != idTable.table.end() && std::count_if(idTable.table.begin(), idTable.table.end(), [&](const auto& v) {
		            return std::string(v.id) == std::string(idTableEntry->id) && std::string(v.parrent_function) == std::string(idTableEntry->parrent_function) && v.idtype == 4;
		        }) == 0)
		    {
		        if (idTableEntry->iddatatype == TypeOfVar::STR)
		        {
		            idTable.table.push_back({
		                const_cast<char*>(brackets.top().first.c_str()),
		                str_number,
		                const_cast<char*>(last_id.c_str()),
		                idTableEntry->iddatatype,
		                4,
		                word
		            });
		        }
		        else
		        {
		        	//std::cout << word << std::endl;
			    	std::string let_val = brackets.top().first.c_str() + std::to_string(str_number);
		            idTable.table.push_back({
		                const_cast<char*>(brackets.top().first.c_str()),
		                str_number,
		                const_cast<char*>(let_val.c_str()),
		                2,
		                4,
		                word
		            });
		            let_val.clear();		        	
		        }
		    }
		    else
		    {
		    	//std::cout << idTableEntry->iddatatype << '\t' << idTableEntry->id << '\t' << word << '\n';
		        auto islexTableEntry = [&](const auto& v) {
		            return v.id == last_id && v.idtype == 4 && brackets.top().first == v.parrent_function;
		        };

		        auto lexTableEntry = std::find_if(idTable.table.begin(), idTable.table.end(), islexTableEntry);

		        if(lexTableEntry != idTable.table.end())
		        {
			        if(lexTableEntry->iddatatype == TypeOfVar::STR && lexTableEntry->idtype == 4)
			        {
						lexTableEntry->value = word;
			        }
		        }
				else
		        {
			    	std::string let_val = brackets.top().first.c_str() + std::to_string(str_number);
		            idTable.table.push_back({
		                const_cast<char*>(brackets.top().first.c_str()),
		                str_number,
		                const_cast<char*>(let_val.c_str()),
		                2,
		                4,
		                word
		            });
		            let_val.clear();		        	
		        }
		    }
		    word.clear();
		    return true;
		}
		else if (FST::execute<INTEGER_LITERAL>(word))
		{
		    lexTable.table.push_back({LEX_LITERAL, str_number, LT_TI_NULLXDX});

			auto isIdTableEntry = [&](const auto& v) {
			    return v.id == last_id && v.idtype == 1 && brackets.top().first == v.parrent_function;
			};

			auto idTableEntry = std::find_if(idTable.table.begin(), idTable.table.end(), isIdTableEntry);

			if (idTableEntry != idTable.table.end() && std::count_if(idTable.table.begin(), idTable.table.end(), [&](const auto& v) {
			    return std::string(v.id) == std::string(idTableEntry->id) && std::string(v.parrent_function) == std::string(idTableEntry->parrent_function) && v.idtype == 4;
			}) == 0)
			{
		        if (last_id.empty())
		        {
		            throw ERROR_THROW_IN(606, str_number, pos);
		        }
		        else
		        {
		        	//std::cout << "IDDATATYPE " << idTableEntry->iddatatype << '\t' << idTableEntry->id << '\t' << idTableEntry->idtype << std::endl;
		            if (idTableEntry->iddatatype == TypeOfVar::INT)
		            {
		                int int_value = boost::lexical_cast<int>(word);
		                idTable.table.push_back({
		                    const_cast<char*>(brackets.top().first.c_str()),
		                    str_number,
		                    const_cast<char*>(last_id.c_str()),
		                    idTableEntry->iddatatype,
		                    4,
		                    int_value
		                });
		            }
		            else if (idTableEntry->iddatatype == TypeOfVar::BOOL)
		            {
		                bool bool_value = boost::lexical_cast<bool>(word);
		                idTable.table.push_back({
		                    const_cast<char*>(brackets.top().first.c_str()),
		                    str_number,
		                    const_cast<char*>(last_id.c_str()),
		                    idTableEntry->iddatatype,
		                    4,
		                    bool_value
		                });
		            }
		            else if (idTableEntry->iddatatype == TypeOfVar::BYTE)
		            {
		                uint16_t value = boost::lexical_cast<uint16_t>(word);
		                if (value >= std::numeric_limits<uint8_t>::min() && value <= std::numeric_limits<uint8_t>::max())
		                {
		                    uint8_t byte_value = static_cast<uint8_t>(value);
		                    idTable.table.push_back({
		                        const_cast<char*>(brackets.top().first.c_str()),
		                        str_number,
		                        const_cast<char*>(last_id.c_str()),
		                        idTableEntry->iddatatype,
		                        4,
		                        byte_value
		                    });
		                }
		                else
		                {
		                    throw ERROR_THROW_IN(617, str_number, pos);
		                }
		            }
		            else
		            {
		                throw ERROR_THROW_IN(607, str_number, pos);
		            }
		        }
		    }
		    else
		    {
				auto islexTableEntry = [&](const auto& v) {
				    return v.id == last_id && v.idtype == 4 && brackets.top().first == v.parrent_function;
				};

				auto lexTableEntry = std::find_if(idTable.table.begin(), idTable.table.end(), islexTableEntry);
				if(lexTableEntry != idTable.table.end())
		        {
			        if (lexTableEntry->iddatatype == TypeOfVar::INT && lexTableEntry->idtype == 4)
			        {
			            lexTableEntry->value = boost::lexical_cast<int>(word);
			        }
			        else if (lexTableEntry->iddatatype == TypeOfVar::BOOL && lexTableEntry->idtype == 4)
			        {
			            lexTableEntry->value = boost::lexical_cast<bool>(word);
			        }
			        else if (lexTableEntry->iddatatype == TypeOfVar::BYTE && lexTableEntry->idtype == 4)
			        {
			            lexTableEntry->value = boost::lexical_cast<uint8_t>(word);
			        }
			        else
			        {
			            throw ERROR_THROW_IN(607, str_number, pos);
			        }
			    }
				else
				{
				    if (std::regex_match(word, std::regex("\\d+")))
				    {
				        int int_value = std::stoi(word);
				        std::string let_val = brackets.top().first + std::to_string(str_number);
				        idTable.table.push_back({
				            const_cast<char*>(brackets.top().first.c_str()),
				            str_number,
				            const_cast<char*>(let_val.c_str()),
				            1,
				            4,
				            int_value
				        });
				    }
				}
		    }

		    return true;
		}
		else if(FST::execute<PRINT>(word) && word.size() == PRINT::states)
		{
			lexTable.table.push_back({LEX_PRINT, str_number, LT_TI_NULLXDX});
			its_call = true;
			return true;
		}
		else if((FST::execute<IF>(word) && word.size() == IF::states) || 
			(FST::execute<ELSE>(word) && word.size() == ELSE::states) ||
			(FST::execute<ELIF>(word) && word.size() == ELIF::states))
		{
			std::string let_val = word + std::to_string(str_number) + brackets.top().first;
			if(!AnalysisBlock(line, pos, str_number, lexTable, idTable))
			{
				lexTable.table.push_back({LEX_IF, str_number, LT_TI_NULLXDX});
				if(line.find("=>") == std::string::npos)
				{
					if(its_if_construction) 
					{
						throw ERROR_THROW_IN(130, str_number, pos);
					}
					else its_if_construction = true;
				}
			}
			idTable.table.push_back({
	            const_cast<char*>(brackets.top().first.c_str()),
	            str_number,
	            const_cast<char*>(let_val.c_str()),
	            0,
	            5,					
			});
			return true;
		}
		else if(RPN::isHexNumber(word))
		{
			RPN::transformFromHex(line, word, str_number, pos);
			return true;
		}
		else if(RPN::isBinaryNumber(word))
		{
			RPN::transformFromBinary(line, word);
			return true;
		}
		else if(FST::execute<IDENTIFICATOR>(word))
		{
			return AnalyseIdentificator(word, str_number, pos, lexTable, idTable);
		}
		return false;
	}

	void Analysis::Clear()
	{
		if(brackets.top().second == '}' && brackets.top().first != "glob")
			brackets.pop();
	}

	bool Analysis::AnalyseIdentificator(std::string token, const int& str_number, const int& pos, LT::LexTable& lexTable, IT::IdTable& idTable)
	{
		//std::cout << brackets.top().first << '\t' << brackets.top().second << '\n';
		if(token.size() > 20)
		{
			throw ERROR_THROW_IN(132, str_number, pos);
		}

		if(its_function)
		{
			Clear();
			lexTable.table.push_back({LEX_ID, str_number, type_of_flag.type});
			idTable.table.push_back({ 
				const_cast<char*>(brackets.top().first.c_str()),
				str_number,
				const_cast<char*>(token.c_str()),
				type_of_flag.type,
				2
			});
			brackets.push({
				token,
				'\0'
			});
			its_function = false;
		}
		else
		{
		    Clear();
		    lexTable.table.push_back({LEX_ID, str_number, type_of_flag.type});
		    last_id = token;
		    std::string func = brackets.top().first;

		    auto funcExists = std::find_if(idTable.table.begin(), idTable.table.end(), [token, func](const auto& v) {
		        return std::string(v.id) == token && v.idtype == 2;
		    });

		    if(funcExists != idTable.table.end() && !its_function_call)
		    {
		    	throw ERROR_THROW_IN(605, str_number, pos);
		    }
		    else if(funcExists != idTable.table.end() && its_function_call)
	    	{
		        idTable.table.push_back({
		            const_cast<char*>(brackets.top().first.c_str()),
		            str_number,
		            const_cast<char*>(token.c_str()),
		            0,
		            2
		        });	    		
	    	}

		    auto variableExists = std::find_if(idTable.table.begin(), idTable.table.end(), [token, func](const auto& v) {
		        return std::string(v.id) == token && v.parrent_function == func && v.idtype == 1;
		    });

		    auto variableCount = std::count_if(idTable.table.begin(), idTable.table.end(), [token, func](const auto& v) {
		        return std::string(v.id) == token && v.parrent_function == func && v.idtype != 6;
		    });

            if (variableExists == idTable.table.end()) 
            {
                while (brackets.top().first != "glob") 
                {
                    removedBrackets.push(brackets.top());
                    brackets.pop();
                    variableExists = std::find_if(idTable.table.begin(), idTable.table.end(), [token, parent_function = brackets.top().first](const auto& v) {
                        return v.id == token && v.idtype == static_cast<IDTYPE>(4) && v.parrent_function == parent_function;
                    });
                    if (variableExists != idTable.table.end())
                        break;
                }
            }

            while (!removedBrackets.empty()) 
            {
                brackets.push(removedBrackets.top());
                removedBrackets.pop();
            }

		    if (variableExists == idTable.table.end())
		    {
		        int idtype = 1;
		        if (brackets.top().second != '{') idtype = 3;
		        idTable.table.push_back({
		            const_cast<char*>(brackets.top().first.c_str()),
		            str_number,
		            const_cast<char*>(token.c_str()),
		            type_of_flag.type,
		            idtype
		        });

		        if (idtype == 1)
		            id_vision.push_back({
		                brackets.top().first,
		                {token}
		            });
		    }
		    else if(variableCount > 1 && type_of_flag.type != TypeOfVar::DEF)
		    {
		    	throw ERROR_THROW_IN(605, str_number, pos);
		    }
		    else
		    {
		    	//std::cout << token << '\t' << str_number << '\n';
		        idTable.table.push_back({
		            const_cast<char*>(brackets.top().first.c_str()),
		            str_number,
		            const_cast<char*>(token.c_str()),
		            variableExists->iddatatype,
		            6
		        });
		        its_call = false;
		    }

		    func.clear();
		}
		return true;
	}

	bool Analysis::AnalysisSymbol(char token, std::string& line, int pos, int str_number, LT::LexTable& lexTable, IT::IdTable& idTable)
	{
		switch(token)
		{
			case LEX_EQUAL_SIGN:
			{
				lexTable.table.push_back({'v', str_number, LT_TI_NULLXDX});
				if(!its_lambda)
					polish_notation.transform(line, brackets, type_of_flag.type, pos, str_number, lexTable, idTable);
				type_of_flag.type = TypeOfVar::DEF;
				return true;
			}
			case LEX_DIRSLASH:
			{
				lexTable.table.push_back({'v', str_number, LT_TI_NULLXDX});
				return true;
			}
			case LEX_STAR:
			{
				lexTable.table.push_back({'v', str_number, LT_TI_NULLXDX});
				return true;				
			}
			case LEX_PLUS:
			{
				lexTable.table.push_back({'v', str_number, LT_TI_NULLXDX});
				return true;
			}
			case LEX_MINUS:
			{
				lexTable.table.push_back({'v', str_number, LT_TI_NULLXDX});
				return true;
			}
			case LEX_RIGHTHESIS:
			{
				lexTable.table.push_back({LEX_RIGHTHESIS, str_number, LT_TI_NULLXDX});
				return true;
			}
			case LEX_LEFTHESIS:
			{
				lexTable.table.push_back({LEX_LEFTHESIS, str_number, LT_TI_NULLXDX});
				return true;
			}
			case LEX_COLON:
			{
				lexTable.table.push_back({'v', str_number, LT_TI_NULLXDX});
				CheckCallFunction(line, str_number, pos, lexTable, idTable);
				type_of_flag.type = TypeOfVar::DEF;
				return true;
			}
			case LEX_LEFTBRACE:
			{
				lexTable.table.push_back({LEX_LEFTBRACE, str_number, LT_TI_NULLXDX});
				if(its_if_construction) brackets.push({brackets.top().first + std::to_string(str_number), LEX_LEFTBRACE});
				brackets.top().second = LEX_LEFTBRACE; 
				return true;				
			}
			case LEX_RIGHTBRACE:
			{
				lexTable.table.push_back({LEX_RIGHTBRACE, str_number, LT_TI_NULLXDX});
				brackets.top().second = LEX_RIGHTBRACE;
				if(its_if_construction) {Clear(); its_if_construction = false; } 
				return true;
			}
			case LEX_BIG:
			{
				lexTable.table.push_back({LEX_BIG, str_number, LT_TI_NULLXDX});
				return true;				
			}
			case LEX_SMALL:
			{
				lexTable.table.push_back({LEX_SMALL, str_number, LT_TI_NULLXDX});
				return true;				
			}
			case LEX_COMMA:
			{
				lexTable.table.push_back({LEX_COMMA, str_number, LT_TI_NULLXDX});
				return true;
			}
			case LEX_SEMICOLON:
			{
				lexTable.table.push_back({LEX_SEMICOLON, str_number, LT_TI_NULLXDX});
				if(its_lambda)   its_lambda = false;
				if(its_function_call) its_function_call = false;
				last_id.clear();
				return true;
			}
			case LEX_LEFTBLOCK:
			{
				lexTable.table.push_back({LEX_LEFTBLOCK, str_number, LT_TI_NULLXDX});
				return true;
			}
			case LEX_RIGHTBLOCK:
			{
				lexTable.table.push_back({LEX_RIGHTBLOCK, str_number, LT_TI_NULLXDX});
				return true;
			}
			default:
			{
				return false;
			}
		}
	}
}