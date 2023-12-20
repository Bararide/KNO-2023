#include "translator.h"

namespace ASM
{
// #define	LEX_TYPE		't'				
// #define	LEX_ID			'i'			
// #define	LEX_LITERAL		'l'			
// #define	LEX_FUNCTION	'f'			
// #define	LEX_DECLARE		'd'			
// #define	LEX_RETURN		'r'			
// #define	LEX_PRINT		'p'
// #define LEX_IF          'e'	
// #define	LEX_SEMICOLON	';'			
// #define	LEX_COMMA		','			
// #define	LEX_LEFTBRACE	'{'			
// #define	LEX_RIGHTBRACE	'}'			
// #define	LEX_LEFTHESIS	'('			
// #define	LEX_RIGHTHESIS	')'
// #define	LEX_LEFTBLOCK	'['			
// #define	LEX_RIGHTBLOCK	']'
// #define LEX_BIG         '>'
// #define LEX_SMALL       '<'
// #define	LEX_PLUS		'<<'			
// #define	LEX_MINUS		'-'			
// #define	LEX_STAR		'*'			
// #define	LEX_DIRSLASH	'/'
// #define	LEX_EQUAL_SIGN	'='	
// #define LEX_COLON       ':'	
// #define LEX_OPERATOR	'o'
	void Translator::transform_data_generator(LT::LexTable& lexTable, IT::IdTable& idTable)
	{
		if(stream.is_open())
		{
			stream << INCL << DATA << FORMAT;
			for(const auto& entry : idTable.table)
			{
				if(entry.idtype == static_cast<IT::IDTYPE>(4))
				{
					if(entry.iddatatype == static_cast<IT::IDDATATYPE>(1))
					{
						stream << '\t' << entry.id << " dd ";
						std::visit([this](const auto& v){
					        stream << v << '\n';
						}, entry.value);
					}
					else if(entry.iddatatype == static_cast<IT::IDDATATYPE>(4))
					{
						stream << '\t' << entry.id << " db ";
						std::visit([this](const auto& v){
							stream << v << '\n';
						}, entry.value);
					}
					else if(entry.iddatatype == static_cast<IT::IDDATATYPE>(5))
					{
						stream << '\t' << entry.id << " db ";
						std::visit([this](const auto& v){
					        stream << v << '\n';
						}, entry.value);
					}
					else if (entry.iddatatype == static_cast<IT::IDDATATYPE>(2))
					{
					    stream << '\t' << entry.id << " db ";
					    std::visit([this](const auto& v) {
					        using T = std::decay_t<decltype(v)>;
					        if constexpr (std::is_same_v<T, std::string>)
					        {
					            const std::string& str = static_cast<const std::string&>(v);
					            stream << str << ", " << "0xA" << ", 0\n" << "\tlength";
					        }
					    }, entry.value);
					    stream << entry.id << " equ $ - " << entry.id << '\n';
					}
				}
			}
			stream << BSS << START;
			generator(lexTable, idTable);
		}
	}

	void Translator::generator(LT::LexTable& lexTable, IT::IdTable& idTable)
	{
		std::string ifBlock;
		std::string mainBlock;
		std::string elseBlock;

		std::string blockName;
		std::string ifName;
		std::string elseName;

		int i = 0;
		int par_count = 0;

		bool is_if_block       = false;
		bool is_function_block = false;
		bool is_short_operator = false;
		bool is_else_block     = false;
		bool is_call_param     = false;

		for(auto lex : lexTable.table)
		{
			switch(lex.lexema)
			{
				case LEX_FUNCTION:
				{
			        auto iter = std::find_if(idTable.table.begin(), idTable.table.end(), [&lex](const auto& v){
			            return v.firstApi == lex.sn && v.idtype == 2;
			        });
			        if (iter != idTable.table.end()) 
			        {
			        	blockName = iter->id;
			            mainBlock += std::string(iter->id) + ":\n";
			        }
			        is_function_block = true;
			        break;
				}
				case LEX_IF:
				{
				    auto iter = std::find_if(idTable.table.begin(), idTable.table.end(), [&lex](const auto& v){
				        return v.firstApi == lex.sn && v.idtype == 5;
				    });
				    if (iter != idTable.table.end() && std::string(iter->id).find("else") == std::string::npos) 
				    {
				    	is_if_block = true;
				    	++i;
				    }
				    else if(iter != idTable.table.end() && std::string(iter->id).find("else") != std::string::npos) 
				    {
				    	is_else_block = true;
				    }

				    iter = std::find_if(idTable.table.begin(), idTable.table.end(), [&lex](const auto& v){
				        return v.firstApi == lex.sn && v.idtype == 4;
				    });

				    if (iter != idTable.table.end())
				    {
				    	if(is_if_block)
				    	{
				    		mainBlock += "\tcmp dword [" + std::string(iter->id) + "], 1\n";
				    		mainBlock += "\tjne end" + blockName + boost::lexical_cast<std::string>(i + 1) + "\n";
				    		mainBlock += "end" + blockName + boost::lexical_cast<std::string>(i) + ":\n";
				    	}
				    }

				    break;
				}
			    case LEX_OPERATOR:
			    {
			    	is_short_operator = true;
			    	break;
			    }
			    case LEX_SEMICOLON:
			    {
			    	if(is_short_operator && is_function_block)
			    	{
			    		stream << mainBlock;
			    		is_short_operator = false;
			    		mainBlock.clear();
			    	}

			    	if(is_short_operator && is_if_block) 
			    	{
			    		stream << ifBlock;
			    		is_short_operator = false;
			    		ifBlock.clear();
			    	}
			    	is_call_param = false;
			    	par_count = 0;
			    	break;
			    }
				case LEX_LEFTBRACE:
				{
					break;
				}
				case LEX_RIGHTBRACE:
				{
					++i;
					if (is_if_block)
					{
						mainBlock += "\tjmp end" + blockName + boost::lexical_cast<std::string>(i + 1) + '\n';
						is_if_block = false;
						ifBlock.clear();
					}

					if (is_else_block)
					{
						mainBlock += "\tjmp end" + blockName + boost::lexical_cast<std::string>(i) + '\n';
						is_else_block = false;
					}

					if (is_function_block)
					{
						is_function_block = false;
					}

					mainBlock += "end" + blockName + boost::lexical_cast<std::string>(i) + ":\n";
					break;
				}
			    case LEX_PRINT:
			    {
			        auto iter = std::find_if(idTable.table.begin(), idTable.table.end(), [&lex](const auto& v){
			            return v.firstApi == lex.sn && v.idtype == 4;
			        });    

			        if (iter != idTable.table.end()) 
			        {
			            if (iter->iddatatype == static_cast<IT::IDDATATYPE>(2)) 
			            {
			                mainBlock += "\tmov rdi, 1\n\tmov rsi, " + std::string(iter->id) + "\n\tmov rdx, length" + std::string(iter->id) + "\n\tmov rax, 1\n\tsyscall\n";
			            }
			            else 
			            {
			                mainBlock += "\tsub rsp, 8\n\tmov esi, [" + std::string(iter->id) + "]\n\tmov edi, fmtint\n\txor eax, eax\n\tcall printf\n\tadd rsp, 8\n";
			            }
			        }
			        else
			        {
				        iter = std::find_if(idTable.table.begin(), idTable.table.end(), [&lex](const auto& v){
				            return v.firstApi == lex.sn && v.idtype == 6;
				        });	
				        if (iter != idTable.table.end()) 
				        {
				            if (iter->iddatatype == static_cast<IT::IDDATATYPE>(2)) 
				            {
				                mainBlock += "\tmov rdi, 1\n\tmov rsi, " + std::string(iter->id) + "\n\tmov rdx, length" + std::string(iter->id) + "\n\tmov rax, 1\n\tsyscall\n";
				            }
				            else 
				            {
				                mainBlock += "\tsub rsp, 8\n\tmov esi, [" + std::string(iter->id) + "]\n\tmov edi, fmtint\n\txor eax, eax\n\tcall printf\n\tadd rsp, 8\n";
				            }
				        }		        	
			        }
			        break;			
				}
				case LEX_COLON:
				{
					auto iter = std::find_if(idTable.table.begin(),  idTable.table.end(), [&lex](const auto& v){
						return v.firstApi == lex.sn && v.idtype == 2 && v.iddatatype == 0;
					});

					if(iter != idTable.table.end())
					{
						is_call_param = true;
						//mainBlock += ""
					}
					break;
				}
			}
		}			
		stream << mainBlock << END;
	}
}