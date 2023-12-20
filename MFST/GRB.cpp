#include "GRB.h"
#include "Rules.h"

namespace GRB
{
	Rule::Chain::Chain(const std::vector<GRBALPHABET>& chain)
	{
	    this->nt = chain;
	}

	GRB::Rule::Rule(GRBALPHABET pnn, int iderror, const std::vector<GRB::Rule::Chain>& chains)
	{
	    this->nn = pnn;
	    this->iderror = iderror;
	    this->chains = chains;
	}

	Greibach::Greibach(GRBALPHABET pstartN, GRBALPHABET pstbottomT, short psize, const std::vector<Rule>& rules)
	{
	    this->startN = pstartN;
	    this->stbottomT = pstbottomT;
	    this->rules = rules;
	}

	short Greibach::getRule(GRBALPHABET pnn, Rule& prule)
	{
		short rc = -1, k = 0;
		while (k < this->rules.size() && rules.at(k).nn != pnn)
			k++;
		if (k < this->rules.size())
			prule = rules.at(rc = k);

		return rc;
	}

	Rule Greibach::getRule(short n)
	{
		Rule rc;
		if (n < this->rules.size())
		{
			rc = rules.at(n);
		}
		return rc;
	}
	char* Rule::getCRule(char* b, short nchain)
	{
		char buf[200];
		b[0] = Chain::alphabet_to_char(this->nn);
		b[1] = '-';
		b[2] = '>';
		b[3] = 0x00;
		this->chains.at(nchain).getCChain(buf);
		std::string sizeStr = std::to_string(sizeof(buf) + 5);
	    strncat(b, sizeStr.c_str(), 200);
	    strncat(b, " ", 200);
	    strncat(b, buf, 200);

		return b;
	}

	short Rule::getNextChain(GRBALPHABET t, Rule::Chain& pchain, short j)
	{
		short rc = -1;

		while (j < this->chains.size() && this->chains.at(j).nt.at(0) != t)
		{
			j++;
		}

		rc = (j < this->chains.size() ? j : -1);
		if (rc >= 0)
			pchain = chains.at(rc);
		return rc;
	}
	
	char* Rule::Chain::getCChain(char* b)
	{
		for (int i = 0; i < this->nt.size(); ++i)
			b[i] = Chain::alphabet_to_char(this->nt.at(i));
		b[this->nt.size()] = 0;
		return b;
	}
	Greibach getGreibach()
	{
		return greibach;
	}
}