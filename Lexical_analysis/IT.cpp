#include "IT.h"

#include <iostream>

namespace IT
{
	IdTable::IdTable()
	{
		this->noname_lexema_count = 0;
		this->maxsize = TI_MAXSIZE;
		this->size = 0;
	}
	Entry::Entry()
	{
		this->parrent_function[0] = '\0';
		this->id[0] = '\0';
		this->firstApi = 0;
		this->iddatatype = IT::IDDATATYPE::DEF;
		this->idtype = IT::IDTYPE::D;
		this->parmQuantity = 0;
	}

	Entry::Entry(char* parrent_function, int firstApi, char* id, int iddatatype, int idtype, int value)
	{
	    std::strncpy(this->parrent_function, parrent_function, 10);
	    this->parrent_function[10] = '\0';

	    std::strncpy(this->id, id, 10);
	    this->id[10] = '\0';

	    this->firstApi = firstApi;
	    this->iddatatype = static_cast<IDDATATYPE>(iddatatype);
	    this->idtype = static_cast<IDTYPE>(idtype);
	    this->value = value;	
	}

	Entry::Entry(char* parrent_function, int firstApi, char* id, int iddatatype, int idtype, char value)
	{
	    std::strncpy(this->parrent_function, parrent_function, 10);
	    this->parrent_function[10] = '\0';

	    std::strncpy(this->id, id, 10);
	    this->id[10] = '\0';

	    this->firstApi = firstApi;
	    this->iddatatype = static_cast<IDDATATYPE>(iddatatype);
	    this->idtype = static_cast<IDTYPE>(idtype);
	    this->value = value;	
	}

	Entry::Entry(char* parrent_function, int firstApi, char* id, int iddatatype, int idtype, std::string value)
	{
	    std::strncpy(this->parrent_function, parrent_function, 10);
	    this->parrent_function[10] = '\0';

	    std::strncpy(this->id, id, 10);
	    this->id[10] = '\0';

	    this->firstApi = firstApi;
	    this->iddatatype = static_cast<IDDATATYPE>(iddatatype);
	    this->idtype = static_cast<IDTYPE>(idtype);
	    this->value = value;	
	}

	Entry::Entry(char* parrent_function, int firstApi, char* id, int iddatatype, int idtype, bool value)
	{
	    std::strncpy(this->parrent_function, parrent_function, 10);
	    this->parrent_function[10] = '\0';

	    std::strncpy(this->id, id, 10);
	    this->id[10] = '\0';

	    this->firstApi = firstApi;
	    this->iddatatype = static_cast<IDDATATYPE>(iddatatype);
	    this->idtype = static_cast<IDTYPE>(idtype);
	    this->value = value;	
	}

	Entry::Entry(char* parrent_function, int firstApi, char* id, int iddatatype, int idtype)
	{
	    std::strncpy(this->parrent_function, parrent_function, 10);
	    this->parrent_function[10] = '\0';

	    std::strncpy(this->id, id, 10);
	    this->id[10] = '\0';

	    this->firstApi = firstApi;
	    this->iddatatype = static_cast<IDDATATYPE>(iddatatype);
	    this->idtype = static_cast<IDTYPE>(idtype);
	    this->parmQuantity = 0;
	}

	// Entry::Entry(char* parrent_function, int firstApi, char* id, int iddatatype,  int idtype)
	// {
	//     std::strncpy(this->parrent_function, parrent_function, 10);
	//     this->parrent_function[10] = '\0';

	//     std::strncpy(this->id, id, 10);
	//     this->id[10] = '\0';

	//     this->firstApi = firstApi;
	//     this->iddatatype = static_cast<IDDATATYPE>(iddatatype);
	//     this->idtype = static_cast<IDTYPE>(idtype);		
	// }

	void IdTable::PrintIdTable(const char* in)
	{
		std::ofstream* idStream = new std::ofstream;
		idStream->open(in);

		if (idStream->is_open())
		{
			bool flagForFirst = false;

#pragma region Literals

*(idStream) << "\n" << std::endl;
*(idStream) << std::setw(30) << "ЛИТЕРАЛЫ" << std::endl;

			for (const auto& entry : table) 
			{
			    if (entry.idtype == IDTYPE::L) 
			    {
			        std::visit([&idStream](const auto& v) 
			        {
			            *(idStream) << std::setw(25) << v << "\t\t\t-\t\t";
			        }, entry.value);

			        *(idStream) << std::setw(10) << entry.parrent_function << "\t\t" << entry.id << "\t\t\t";

			        switch (entry.iddatatype) 
			        {
			            case IDDATATYPE::INT:
			                *(idStream) << "INT\t\t\t-\t\t";
			                break;
			            case IDDATATYPE::STR:
			                *(idStream) << "STR\t\t\t-\t\t";
			                break;
			            case IDDATATYPE::BOOL:
	                        *(idStream) << "BOOL\t\t\t-\t\t";
	                        break;
	                    case IDDATATYPE::BYTE:
	                        *(idStream) << "BYTE\t\t\t-\t\t";
	                        break;
	                }

	                *(idStream) << entry.firstApi << std::endl;
	            }
	        }

#pragma endregion
			*(idStream) << "\n\n\n";
#pragma region Functions

	        *(idStream) << "\n\n\n\n" << std::endl;
	        *(idStream) << "\t\t\t\t\t\tФункции\n" << std::endl;
	        *(idStream) << std::left << std::setw(15) << "Область" << std::setw(15) << "ID" << std::setw(15) << "Тип" << std::setw(15) << "встреча" << std::setw(15) << "idtype" << std::endl;
	        *(idStream) << std::setfill('-') << std::setw(65) << "-" << std::setfill(' ') << std::endl;

	        for (const auto& entry : table) {
	            if (entry.idtype == IDTYPE::F || entry.idtype == IDTYPE::I) {
	                *(idStream) << std::setw(15) << entry.parrent_function << std::setw(10) << entry.id;

	                switch (entry.iddatatype) {
	                    case IDDATATYPE::INT:
	                        *(idStream) << std::setw(10) << "INT";
	                        break;
	                    case IDDATATYPE::STR:
	                        *(idStream) << std::setw(10) << "STR";
	                        break;
	                    case IDDATATYPE::BOOL:
	                        *(idStream) << std::setw(10) << "BOOL";
	                        break;
	                    case IDDATATYPE::BYTE:
	                        *(idStream) << std::setw(10) << "BYTE";
	                        break;
	                    case IDDATATYPE::DEF:
	                        *(idStream) << std::setw(10) << "DEF";
	                        break;
	                }

	                *(idStream) << std::setw(15) << entry.firstApi << std::setw(15) << entry.idtype << std::endl;
	            }
	        }

#pragma endregion
			* (idStream) << "\n\n\n";
#pragma region Variables

			flagForFirst = false;

			*(idStream) << "\n\n\n\n" << std::endl;
			*(idStream) << "\t\t\t\t\t\tПеременные\n" << std::endl;

			for (int i = 0; i < this->table.size(); i++)
			{
				if (this->table.at(i).idtype == IT::IDTYPE::V)
				{


					switch (this->table.at(i).iddatatype)
					{
					case 1:
					{
						*(idStream) << "   " << this->table.at(i).parrent_function << std::setw(35 - strlen(this->table.at(i).parrent_function)) << this->table.at(i).id << std::setw(20) << "INT " << std::setw(15) << "V" << "\t\t\t" << this->table.at(i).firstApi << std::endl;
						break;
					}
					case 2:
					{
						*(idStream) << "   " << this->table.at(i).parrent_function << std::setw(35 - strlen(this->table.at(i).parrent_function)) << this->table.at(i).id << std::setw(20) << "STR " << std::setw(15) << "V" << "\t\t\t" << this->table.at(i).firstApi << std::endl;
						break;
					}
					case 4:
					{
						*(idStream) << "   " << this->table.at(i).parrent_function << std::setw(35 - strlen(this->table.at(i).parrent_function)) << this->table.at(i).id << std::setw(20) << "BOOL " << std::setw(15) << "V" << "\t\t\t" << this->table.at(i).firstApi << std::endl;
						break;
					}
					case 5:
					{
						*(idStream) << "   " << this->table.at(i).parrent_function << std::setw(35 - strlen(this->table.at(i).parrent_function)) << this->table.at(i).id << std::setw(20) << "BYTE " << std::setw(15) << "A" << "\t\t\t" << this->table.at(i).firstApi << std::endl;
						break;
					}
					}

					flagForFirst = true;
				}

				if (this->table.at(i).idtype == IT::IDTYPE::P)
				{

					switch (this->table.at(i).iddatatype)
					{
					case 1:
					{
						*(idStream) << "   " << this->table.at(i).parrent_function << std::setw(35 - strlen(this->table.at(i).parrent_function)) << this->table.at(i).id << std::setw(20) << "INT " << std::setw(15) << "P" << "\t\t\t" << this->table.at(i).firstApi << std::endl;
						break;
					}
					case 2:
					{
						*(idStream) << "   " << this->table.at(i).parrent_function << std::setw(35 - strlen(this->table.at(i).parrent_function)) << this->table.at(i).id << std::setw(20) << "STR " << std::setw(15) << "P" << "\t\t\t" << this->table.at(i).firstApi << std::endl;
						break;
					}
					case 4:
					{
						*(idStream) << "   " << this->table.at(i).parrent_function << std::setw(35 - strlen(this->table.at(i).parrent_function)) << this->table.at(i).id << std::setw(20) << "BOOL " << std::setw(15) << "P" << "\t\t\t" << this->table.at(i).firstApi << std::endl;
						break;
					}
					case 5:
					{
						*(idStream) << "   " << this->table.at(i).parrent_function << std::setw(35 - strlen(this->table.at(i).parrent_function)) << this->table.at(i).id << std::setw(20) << "BYTE " << std::setw(15) << "A" << "\t\t\t" << this->table.at(i).firstApi << std::endl;
						break;
					}
					}

					flagForFirst = true;
				}

				if (this->table.at(i).idtype == IT::IDTYPE::A)
				{

					switch (this->table.at(i).iddatatype)
					{
					case 1:
					{
						*(idStream) << "   " << this->table.at(i).parrent_function << std::setw(35 - strlen(this->table.at(i).parrent_function)) << this->table.at(i).id << std::setw(20) << "INT " << std::setw(15) << "A" << "\t\t\t" << this->table.at(i).firstApi << std::endl;
						break;
					}
					case 2:
					{
						*(idStream) << "   " << this->table.at(i).parrent_function << std::setw(35 - strlen(this->table.at(i).parrent_function)) << this->table.at(i).id << std::setw(20) << "STR " << std::setw(15) << "A" << "\t\t\t" << this->table.at(i).firstApi << std::endl;
						break;
					}
					case 4:
					{
						*(idStream) << "   " << this->table.at(i).parrent_function << std::setw(35 - strlen(this->table.at(i).parrent_function)) << this->table.at(i).id << std::setw(20) << "BOOL " << std::setw(15) << "A" << "\t\t\t" << this->table.at(i).firstApi << std::endl;
						break;
					}
					case 5:
					{
						*(idStream) << "   " << this->table.at(i).parrent_function << std::setw(35 - strlen(this->table.at(i).parrent_function)) << this->table.at(i).id << std::setw(20) << "BYTE " << std::setw(15) << "A" << "\t\t\t" << this->table.at(i).firstApi << std::endl;
						break;
					}
					}

					flagForFirst = true;
				}


			}

#pragma endregion
			* (idStream) << "\n\n\n";

		}
		else
			throw ERROR_THROW(125);
		idStream->close();
		delete idStream;
	}
}