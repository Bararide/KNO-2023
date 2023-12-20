#ifndef OUT_H
#define OUT_H

#include "In.h"
#include "Parm.h"
#include "../Error_handler/Error.h"

namespace Out
{
	struct OUT
	{
		char outfile[PARM_MAX_SIZE];
		std::ofstream* stream;
	};
	static const OUT INITOUT = { "", NULL };
	OUT getout(char outfile[]);
	void WriteLine(OUT out, const char* c);
	void WriteIn(OUT out, In::IN in);
	void WriteError(OUT out, Error::ERROR error);
	void Close(OUT out);
}

#endif