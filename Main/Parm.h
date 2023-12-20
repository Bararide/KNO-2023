#ifndef PARM_H
#define PARM_H

#include <fstream>
#include <cstddef>
#include <iostream>
#include <cstring>

using std::endl; using std::cin; using std::cout; 
using std::fstream; using std::ofstream; using std::ifstream;

#include "In.h"
#include "../Error_handler/Error.h"

#define PARM_IN "-in:"
#define PARM_OUT "-out:"
#define PARM_LOG "-log:"
#define PARM_ASM "-asm:"
#define PARM_MAX_SIZE 300
#define PARM_OUT_DEFAULT_EXT ".out"
#define PARM_LOG_DEFAULT_EXT ".log"
#define PARM_ASM_DEFAULT_EXT ".asm"

namespace Parm
{
	struct PARM
	{
		char in[PARM_MAX_SIZE];
		char out[PARM_MAX_SIZE];
		char log[PARM_MAX_SIZE];
		char assem[PARM_MAX_SIZE];
	};

	PARM getparm(int argc, char* argv[]);
}

#endif