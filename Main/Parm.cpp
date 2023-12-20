#include "Parm.h"

namespace Parm
{
	PARM getparm(int argc, char* argv[])
	{	
		PARM parm;
		bool in = false, out = false, log = false;
		for (int i = 1; i < argc; i++)
		{
			if (strlen(argv[i]) > PARM_MAX_SIZE)
				throw ERROR_THROW(104);

			if (strstr(argv[i], PARM_IN))
			{
				strcpy(parm.in, argv[i] + strlen(PARM_IN));
				in = true;
			}
			if (strstr(argv[i], PARM_OUT))
			{
				strcpy(parm.out, argv[i] + strlen(PARM_OUT));
				out = true;
			}
			if (strstr(argv[i], PARM_LOG))
			{
				strcpy(parm.log, argv[i] + strlen(PARM_LOG));
				log = true;
			}
		}
		if (!in) 
			throw ERROR_THROW(100);
		if (!out)
		{
			strcpy(parm.out, parm.in);
			strcat(parm.out, PARM_OUT_DEFAULT_EXT);
		}
		if (!log)
		{
			strcpy(parm.log, parm.in);
			strcat(parm.log, PARM_LOG_DEFAULT_EXT);
		}
		return parm;
	}
}
		
