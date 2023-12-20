
#ifndef LT_H
#define LT_H

#include "IT.h"
#include "../Error_handler/Error.h"

#include <vector>

#define LEXEMA_FIXSIZE  1
#define	LT_MAXSIZE		4096
#define	LT_TI_NULLXDX	-1					
#define	LEX_TYPE		't'				
#define	LEX_ID			'i'			
#define	LEX_LITERAL		'l'			
#define	LEX_FUNCTION	'f'			
#define	LEX_DECLARE		'd'			
#define	LEX_RETURN		'r'			
#define	LEX_PRINT		'p'
#define LEX_IF          'e'	
#define	LEX_SEMICOLON	';'			
#define	LEX_COMMA		','			
#define	LEX_LEFTBRACE	'{'			
#define	LEX_RIGHTBRACE	'}'			
#define	LEX_LEFTHESIS	'('			
#define	LEX_RIGHTHESIS	')'
#define	LEX_LEFTBLOCK	'['			
#define	LEX_RIGHTBLOCK	']'
#define LEX_BIG         '>'
#define LEX_SMALL       '<'
#define	LEX_PLUS		'+'			
#define	LEX_MINUS		'-'			
#define	LEX_STAR		'*'			
#define	LEX_DIRSLASH	'/'
#define	LEX_EQUAL_SIGN	'='	
#define LEX_COLON       ':'	
#define LEX_OPERATOR	'o'	
#define LEX_LIB         'x'
#define LEX_MAIN        'm'
#define LEX_IMPORT      'c'

#define PLUS '+'
#define MINUS '-'
#define STAR '*'
#define DIRSLASH '/'


namespace LT								
{
	struct Entry						
	{
		char lexema;						
		int sn;								
		int idxTI;							
		Entry();
		Entry(const char lex, int str_n, int idxTI);
	};

	struct LexTable						
	{				
		std::vector<Entry> table;					


		Entry GetEntry(					
			int n						
		);

		void PrintLexTable(const char* in);
		LexTable(){}
	};

	void Delete(LexTable& lextable);		
};

#endif