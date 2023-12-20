#include "LT.h"

#include <fstream>
#include <iostream>

namespace LT
{

	Entry LexTable::GetEntry(int n)
	{
		if (n < this->table.size() && n >= 0)
			return this->table.at(n);
		return Entry();
	}

	void LexTable::PrintLexTable(const char* in)
	{
		std::ofstream* lex_stream = new std::ofstream;
		lex_stream->open(in);
		(*lex_stream) << "\t\t\t\t\tТаблица лексем\n";

		if (lex_stream->is_open())
		{
			int num_string = 0;
			for (int i = 0; i < this->table.size();)
			{
				if (num_string == this->table.at(i).sn)
				{
					(*lex_stream) << this->table.at(i++).lexema;
				}
				else
				{
					num_string++;
					if (this->table.at(i).sn != num_string)
					{
						continue;
					}
					(*lex_stream) << '\n' << num_string << ".\t";

					if (num_string == this->table.at(i).sn)
					{
						(*lex_stream) << this->table.at(i++).lexema;
					}
				}
			}
		}
		else
			throw ERROR_THROW(128);
		lex_stream->close();
		delete lex_stream;

	}
	LT::Entry::Entry()
	{
		this->lexema = '\0';
		this->sn = LT_TI_NULLXDX;
		this->idxTI = LT_TI_NULLXDX;
	}

	LT::Entry::Entry(const char lex, int str_n, int idxTI)
	{
		this->lexema = lex;
		this->sn = str_n;
		this->idxTI = idxTI;
	}
}