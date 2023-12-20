#ifndef MFST_H
#define MFST_H

#include "GRB.h"
#include "../Lexical_analysis/LT.h"
#include "../Lexical_analysis/IT.h"

#include <iostream>
#include <iomanip>
#include <stack>
#include <fstream>

class my_stack_SHORT : public std::stack<short> {
public:
	using std::stack<short>::c;
};

#define MFST_DIAGN_MAXSIZE 2*ERROR_MAXSIZE_MESSAGE
#define MFST_DIAGN_NUMBER 3

static int FST_TRACE_n = -1;
static char rbuf[205], sbuf[205], lbuf[1024];





#define MFST_TRACE1       outputFile << std::setw(4) << std::left << ++FST_TRACE_n << ": " \
                                  << std::setw(20) << std::left << rule.getCRule(rbuf, nrulechain) \
                                  << std::setw(30) << std::left << getCLenta(lbuf, lenta_position) \
                                  << std::setw(20) << std::left << getCSt(sbuf) \
                                  << std::endl;

#define MFST_TRACE2       outputFile << std::setw(4) << std::left << FST_TRACE_n << ": " \
                                  << std::setw(20) << std::left << " " \
                                  << std::setw(30) << std::left << getCLenta(lbuf, lenta_position) \
                                  << std::setw(20) << std::left << getCSt(sbuf) \
                                  << std::endl;

#define MFST_TRACE3       outputFile << std::setw(4) << std::left << ++FST_TRACE_n << ": " \
                                  << std::setw(20) << std::left << " " \
                                  << std::setw(30) << std::left << getCLenta(lbuf, lenta_position) \
                                  << std::setw(20) << std::left << getCSt(sbuf) \
                                  << std::endl;

#define MFST_TRACE4(c)    outputFile << std::setw(4) << std::left << ++FST_TRACE_n << ": " << std::setw(20) << std::left << c << std::endl;
#define MFST_TRACE5(c)    outputFile << std::setw(4) << std::left << FST_TRACE_n << ": " << std::setw(20) << std::left << c << std::endl;
#define MFST_TRACE6(c, k) outputFile << std::setw(4) << std::left << FST_TRACE_n << ": " << std::setw(20) << std::left << c << k << std::endl;
#define MFST_TRACE7       outputFile << std::setw(4) << std::left << state.lenta_position << ": " \
                            << std::setw(20) << std::left << rule.getCRule(rbuf, state.nrulechain) \
                            << std::endl;


typedef my_stack_SHORT MFSTSTSTACK;

namespace MFST
{
	struct MfstState
	{
		short lenta_position;
		short nrule;				
		short nrulechain;			
		MFSTSTSTACK st;
		MfstState();
		MfstState(short pposition, MFSTSTSTACK pst, short pnrulechain);
		MfstState(short pposition, MFSTSTSTACK pst, short pnrule, short pnrulechain);

	};
	class my_stack_MfstState :public std::stack<MfstState> {
	public:
		using std::stack<MfstState>::c;
	};
	struct Mfst							
	{
		std::ofstream outputFile;

		enum RC_STEP {
			NS_OK,					
			NS_NORULE,				
			NS_NORULECHAIN,			
			NS_ERROR,
			TS_OK,					
			TS_NOK,					
			LENTA_END,				
			SURPRISE,			
		};
		struct MfstDiagnosis
		{
			short lenta_position;	
			short nrule;			
			short nrule_chain;
			RC_STEP rc_step;
					
			MfstDiagnosis();		
			MfstDiagnosis(short plenta_position, RC_STEP prc_step, short pnrule, short pnrule_chain);

		} diagnosis[MFST_DIAGN_NUMBER];

		std::vector<GRBALPHABET> lenta;
		short lenta_position;
		short nrule;
		short nrulechain;

		GRB::Greibach grebach;
		LT::LexTable lex;
		MFSTSTSTACK st;	
		my_stack_MfstState storestate;
		Mfst();
		Mfst(LT::LexTable& plex, GRB::Greibach pgrebach);
		char* getCSt(char* buf);
		char* getCLenta(char* buf, short pos, short n = 25);
		char* getDiagnosis(short n, char* buf);
		bool savestate();
		bool resetstate();
		bool push_chain(GRB::Rule::Chain chain);
		RC_STEP step();						
		bool start();						
		bool savediagnosis(RC_STEP pprc_step);
		void printrules();					

		struct Deducation
		{
			short size;
			std::vector<short> nrules;
			std::vector<short> nrulechains;
			Deducation()
			{
				size = 0;
				nrules.clear();
				nrulechains.clear();
			};
		}deducation;

		bool savededucation();
	};
}

#endif