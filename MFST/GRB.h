#ifndef GRB_H
#define GRB_H

#include "../Error_handler/Error.h"

#include <string>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <vector>

typedef short GRBALPHABET;
namespace GRB
{
	struct Rule
	{
		GRBALPHABET nn;
		int iderror;
		struct Chain
		{
			std::vector<GRBALPHABET> nt;
			Chain(){};
			Chain(const std::vector<GRBALPHABET>& chain);
			char* getCChain(char* b);

			
			static GRBALPHABET T(char t) { return GRBALPHABET(t); };
			static GRBALPHABET N(char n) { return -GRBALPHABET(n); };

			static bool isT(GRBALPHABET s) { return s > 0; };
			static bool isN(GRBALPHABET s) { return !isT(s); };

			static char alphabet_to_char(GRBALPHABET s)					
			{
				return isT(s) ? char(s) : char(-s);
			};
		};

		std::vector<Chain> chains;
		Rule()
		{
			this->nn = 0x00;
		}
		Rule(GRBALPHABET pnn, int iderror, const std::vector<Chain>& chains);

		char* getCRule(char* b, short nchain);
		short getNextChain(GRBALPHABET t, Rule::Chain& pchain, short j);
	};
	struct Greibach	
	{		
		GRBALPHABET startN;	
		GRBALPHABET stbottomT;	
		std::vector<Rule> rules;	
		Greibach() {this->startN = 0; this->stbottomT = 0; this->rules.resize(6); };
		Greibach(GRBALPHABET pstartN, GRBALPHABET pstbottomT, short psize, const std::vector<Rule>& rules);
		short getRule(GRBALPHABET pnn, Rule& prule);
		Rule getRule(short n);
	};
	Greibach getGreibach();
}

#endif