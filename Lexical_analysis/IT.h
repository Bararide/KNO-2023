#ifndef IT_H
#define IT_H

#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <cstdlib>
#include <variant>
#include <vector>
#include <any>

#include "../Error_handler/Error.h"
#include "../Meta/Meta.h"

using namespace VARIANT;

#define ID_MAXSIZE		5
#define TI_MAXSIZE		4096			
#define TI_INT_DEFAULT  0x00000000	
#define TI_STR_DEFAULT  0x00			
#define TI_NULLIDX		0xffffffff
#define TI_STR_MAXSIZE  255	

#define PARM_ID ".id.txt"

namespace IT
{
	enum IDDATATYPE { DEF = 0, INT = 1, STR = 2, FUN = 3, BOOL = 4, BYTE = 5, ARG = 6};
	enum IDTYPE { D = 0, V = 1, F = 2, P = 3, L = 4, I = 5, A = 6 };

	struct Entry
	{
		char parrent_function[ID_MAXSIZE + 5];
		int firstApi;
		char id[ID_MAXSIZE + 5];
		IDDATATYPE iddatatype;
		IDTYPE idtype;
		std::variant<int, char, std::string, bool> value;
		int parmQuantity;

		Entry();
		Entry(char* parrent_function, int firstApi, char* id, int iddatatype, int idtype);
		Entry(char* parrent_function, int firstApi, char* id, int iddatatype, int idtype, int value);
		Entry(char* parrent_function, int firstApi, char* id, int iddatatype, int idtype, char value);
		Entry(char* parrent_function, int firstApi, char* id, int iddatatype, int idtype, bool value);
		Entry(char* parrent_function, int firstApi, char* id, int iddatatype, int idtype, std::string value);
	};

	struct IdTable
	{
		int noname_lexema_count;
		int maxsize;
		int size;
		std::vector<Entry> table;

		void PrintIdTable(const char* in);
		IdTable();
	};
	void Delete(IdTable& idtable);
};

#endif