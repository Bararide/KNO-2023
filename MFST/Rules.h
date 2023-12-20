#pragma once
#include "GRB.h"

#define GRB_ERROR_SERIES 600
#define NS(n) GRB::Rule::Chain::N(n)
#define TS(n) GRB::Rule::Chain::T(n)
#define ISNS(n)	GRB::Rule::Chain::isN(n)

namespace GRB
{
	Greibach greibach(NS('S'), TS('$'), 9, {
	    Rule(NS('S'), GRB_ERROR_SERIES + 0, {
	    	Rule::Chain({TS('c'), NS('S')}),
	        Rule::Chain({TS('i'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), TS(';')}),
	        Rule::Chain({TS('f'), TS('['), TS('t'), TS(']'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), NS('S')}),
	        Rule::Chain({TS('f'), TS('['), TS('t'), TS(']'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}')}),
	        Rule::Chain({TS('f'), TS('['), TS('t'), TS(']'), TS('i'), TS('('), TS(')'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), NS('S')}),
	        Rule::Chain({TS('f'), TS('['), TS('t'), TS(']'), TS('i'), TS('('), TS(')'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}')}),

	        Rule::Chain({TS('f'), TS('['), TS('t'), TS(']'), TS('m'), TS('('), TS(')'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}')}),
	        Rule::Chain({TS('f'), TS('['), TS('t'), TS(']'), TS('m'), TS('('), TS(')'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), NS('S')}),

	        Rule::Chain({TS('f'), TS('['), TS('t'), TS(']'), TS('i'), TS('('), TS(')'), TS('o'), TS('('), NS('E'), TS(')'), TS(';'), NS('S')}),
	        Rule::Chain({TS('f'), TS('['), TS('t'), TS(']'), TS('i'), TS('('), TS(')'), TS('o'), TS('('), NS('E'), TS(')'), TS(';')}),

	        Rule::Chain({TS('f'), TS('['), TS('t'), TS(']'), TS('i'), TS('('), NS('F'), TS(')'), TS('o'), TS('('), NS('E'), TS(')'), TS(';'), NS('S')}),
	        Rule::Chain({TS('f'), TS('['), TS('t'), TS(']'), TS('i'), TS('('), NS('F'), TS(')'), TS('o'), TS('('), NS('E'), TS(')'), TS(';')}),

	        Rule::Chain({TS('t'), TS('i'), TS(':'), TS('i'), TS('('), NS('W'), TS(')'), TS(';'), NS('S')}),
	        Rule::Chain({TS('t'), TS('i'), TS(':'), TS('i'), TS('('), NS('W'), TS(')'), TS(';')}),

	        Rule::Chain({TS('i'), TS(':'), TS('i'), TS('('), NS('W'), TS(')'), TS(';'), NS('S')}),
	        Rule::Chain({TS('i'), TS(':'), TS('i'), TS('('), NS('W'), TS(')'), TS(';')}),

	        Rule::Chain({TS('t'), TS('i'), TS(';')}),
	        Rule::Chain({TS('i'), TS('v'), NS('E'), TS(';')}),
	        Rule::Chain({TS('t'), TS('i'), TS('v'), NS('E'), TS(';')}),
	        Rule::Chain({TS('t'), TS('i'), TS(';'), NS('S')}),
	        Rule::Chain({TS('i'), TS('v'), NS('E'), TS(';'), NS('S')}),
	        Rule::Chain({TS('t'), TS('i'), TS('v'), NS('E'), TS(';'), NS('S')})
	    }),
	    Rule(NS('N'), GRB_ERROR_SERIES + 10, {
	        Rule::Chain({TS('t'), TS('i'), TS(';'), NS('N')}),
	        Rule::Chain({TS('t'), TS('i'), TS(';'), NS('S')}),

	        Rule::Chain({TS('e'), TS('('), NS('E'), TS(')'), NS('H')}),
	        Rule::Chain({TS('e'), NS('H')}),

	        Rule::Chain({TS('['), TS('t'), TS(','), TS('l'), TS(']'), TS('i'), TS('('), NS('E'), TS(')'), TS(';'), NS('N')}),
	        Rule::Chain({TS('['), TS('t'), TS(','), TS('i'), TS(']'), TS('i'), TS('('), NS('E'), TS(')'), TS(';'), NS('N')}),

	        Rule::Chain({TS('t'), TS('['), TS('c'), TS(']'), TS('i'), TS(':'), TS('i'), TS('('), NS('W'), TS(')'), TS(';'), NS('N')}),
	        Rule::Chain({TS('t'), TS('['), TS('c'), TS(']'), TS('i'), TS(':'), TS('i'), TS('('), NS('W'), TS(')'), TS(';')}),

	        Rule::Chain({TS('i'), TS(':'), TS('i'), TS('('), NS('W'), TS(')'), TS(';'), NS('N')}),
	        Rule::Chain({TS('i'), TS(':'), TS('i'), TS('('), NS('W'), TS(')'), TS(';')}),

	        Rule::Chain({TS('t'), TS('i'), TS(';')}),
	        Rule::Chain({TS('i'), TS('v'), NS('E'), TS(';')}),
	        Rule::Chain({TS('t'), TS('i'), TS('v'), NS('E'), TS(';')}),
	        Rule::Chain({TS('t'), TS('i'), TS('v'), NS('E'), TS(';'), NS('N')}),
	        Rule::Chain({TS('t'), TS('i'), TS('v'), NS('E'), TS(';'), NS('S')}),
	        Rule::Chain({TS('r'), NS('E'), TS(';'), TS('}'), NS('S')}),
	        Rule::Chain({TS('r'), NS('E'), TS(';'), TS('}')}),
	        Rule::Chain({TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS(';')}),
	        Rule::Chain({TS('t'), TS('i'), TS(';'), NS('N')}),
	        Rule::Chain({TS('r'), NS('E'), TS(';'), NS('N')}),
	        Rule::Chain({TS('i'), TS('v'), NS('E'), TS(';'), NS('N')}),
	        Rule::Chain({TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS(';'), NS('N')}),
	        Rule::Chain({TS('p'), TS('('), NS('P'), TS(')'), TS(';')}),
	        Rule::Chain({TS('p'), TS('('), NS('P'), TS(')'), TS(';'), NS('N')})
	    }),
	    Rule(NS('E'), GRB_ERROR_SERIES + 2, {
	        Rule::Chain({TS('i')}),
	        Rule::Chain({TS('l')}),
	        Rule::Chain({TS('i'), TS(','), NS('E')}),
	        Rule::Chain({TS('l'), TS(','), NS('E')}),
	        Rule::Chain({TS('x'), TS('('), NS('E'), TS(')')}),
	        Rule::Chain({TS('x'), TS('('), TS(')')}),
	        Rule::Chain({TS('('), NS('E'), TS(')')}),
	        Rule::Chain({TS('i'), TS('('), NS('W'), TS(')')}),
	        Rule::Chain({TS('i'), TS('('), TS(')')}),
	        Rule::Chain({TS('i'), NS('M')}),
	        Rule::Chain({TS('l'), NS('M')}),
	        Rule::Chain({TS('('), NS('E'), TS(')'), NS('M')}),
	        Rule::Chain({TS('i'), TS('('), NS('W'), TS(')'), NS('M')}),
	        Rule::Chain({TS('i'), NS('L')}),
	        Rule::Chain({TS('l'), NS('L')})
	    }),
	    Rule(NS('P'), GRB_ERROR_SERIES + 4, {
	        Rule::Chain({TS('i')}),
	        Rule::Chain({TS('l')})
	    }),
	    Rule(NS('L'), GRB_ERROR_SERIES + 3, {
	        Rule::Chain({TS('='), TS('='), TS('i'), TS('o'), NS('L')}),
	        Rule::Chain({TS('>'), TS('='), TS('i'), TS('o'), NS('L')}),
	        Rule::Chain({TS('!'), TS('='), TS('i'), TS('o'), NS('L')}),
	        Rule::Chain({TS('<'), TS('='), TS('i'), TS('o'), NS('L')}),
	        Rule::Chain({TS('='), TS('='), TS('l'), TS('o'), NS('L')}),
	        Rule::Chain({TS('>'), TS('='), TS('l'), TS('o'), NS('L')}),
	        Rule::Chain({TS('!'), TS('='), TS('l'), TS('o'), NS('L')}),
	        Rule::Chain({TS('<'), TS('='), TS('l'), TS('o'), NS('L')}),
	        Rule::Chain({TS('='), TS('i'), TS('o'), NS('L')}),
	        Rule::Chain({TS('>'), TS('i'), TS('o'), NS('L')}),
	        Rule::Chain({TS('!'), TS('i'), TS('o'), NS('L')}),
	        Rule::Chain({TS('<'), TS('i'), TS('o'), NS('L')}),
	        Rule::Chain({TS('='), TS('l'), TS('o'), NS('L')}),
	        Rule::Chain({TS('>'), TS('l'), TS('o'), NS('L')}),
	        Rule::Chain({TS('!'), TS('l'), TS('o'), NS('L')}),
	        Rule::Chain({TS('<'), TS('l'), TS('o'), NS('L')}),

	        Rule::Chain({TS('='), TS('='), TS('i')}),
	        Rule::Chain({TS('>'), TS('='), TS('i')}),
	        Rule::Chain({TS('!'), TS('='), TS('i')}),
	        Rule::Chain({TS('<'), TS('='), TS('i')}),
	        Rule::Chain({TS('='), TS('='), TS('l')}),
	        Rule::Chain({TS('>'), TS('='), TS('l')}),
	        Rule::Chain({TS('!'), TS('='), TS('l')}),
	        Rule::Chain({TS('<'), TS('='), TS('l')}),
	        Rule::Chain({TS('='), TS('i')}),
	        Rule::Chain({TS('>'), TS('i')}),
	        Rule::Chain({TS('!'), TS('i')}),
	        Rule::Chain({TS('<'), TS('i')}),
	        Rule::Chain({TS('='), TS('l')}),
	        Rule::Chain({TS('>'), TS('l')}),
	        Rule::Chain({TS('!'), TS('l')}),
	        Rule::Chain({TS('<'), TS('l')})
	    }),	    
	    Rule(NS('W'), GRB_ERROR_SERIES + 3, {
	        Rule::Chain({TS('i')}),
	        Rule::Chain({TS('l')}),
	        Rule::Chain({TS('i'), TS(','), NS('W')}),
	        Rule::Chain({TS('l'), TS(','), NS('W')})
	    }),
	    Rule(NS('F'), GRB_ERROR_SERIES + 4, {
	        Rule::Chain({TS('['), TS('t'), TS(']'), TS('i')}),
	        Rule::Chain({TS('['), TS('t'), TS(']'), TS('i'), TS(','), NS('F')})
	    }),
	    Rule(NS('M'), GRB_ERROR_SERIES + 2, {
	        Rule::Chain({TS('v'), NS('E')}),
	        Rule::Chain({TS('v'), NS('E'), NS('M')})
	    }),
	    Rule(NS('H'), GRB_ERROR_SERIES + 1, {
	        Rule::Chain({TS('o'), TS('('), NS('N'), TS(')'), TS(';'), NS('N')}),
	        Rule::Chain({TS('o'), TS('('), NS('N'), TS(')'), TS(';')}),
	        Rule::Chain({TS('o'), TS('('), TS(')'), TS(';')}),
	        Rule::Chain({TS('o'), TS('('), NS('N'), TS(')'), TS(';'), NS('S')}),

	        Rule::Chain({TS('o'), NS('N'), TS(';'), NS('N')}),
	        Rule::Chain({TS('o'), NS('N'), TS(';')}),
	        Rule::Chain({TS('o'), TS(';')}),
	        Rule::Chain({TS('o'), NS('N'), TS(';'), NS('S')}),

	        Rule::Chain({TS('{'), NS('N'), TS('}'), NS('N')}),
	        Rule::Chain({TS('{'), TS('}'), NS('N')}),
	        Rule::Chain({TS('{'), TS('}'), NS('S')}),
	        Rule::Chain({TS('{'), NS('S'), TS('}'), NS('S')}),	        
	    })
	});
}