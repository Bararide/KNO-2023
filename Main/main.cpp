#include "Log.h"
#include "Out.h"
#include "Parm.h"
#include "../Error_handler/Error.h"
#include "../Lexical_analysis/LT.h"
#include "../Lexical_analysis/IT.h"
#include "../Lexical_analysis/Lexical_analysis.h"
#include "../Broadcaster/translator.h"
#include "../MFST/MFST.h"

#include <cstdlib>

void CreateByteCode()
{
    std::string command = "nasm -f elf64 -o out.o out.asm && gcc -o out out.o";

    int result = system(command.c_str());

    if (result == 0)
    {
        system("./out");
    }
}

int main(int argc, char* argv[])
{
    Log::LOG log = Log::INITLOG;
    Out::OUT out = Out::INITOUT;
    try
    {
        Parm::PARM parm = Parm::getparm(argc, argv);
        ASM::Translator translator = ASM::Translator();
        log = Log::getlog(parm.log);
        out = Out::getout(parm.out);
        Log::WriteLine(log, "Вывод: ");
        Log::WriteLine(log, "");
        Log::WriteLog(log);
        Log::WriteParm(log, parm);
        In::IN in = In::getin(parm.in);
        Log::WriteIn(log, in);
        Out::WriteIn(out, in);
        LT::LexTable lexTable;
        IT::IdTable	idTable;

        LA::Analysis analysis;
        analysis.FindLex(in, lexTable, idTable);

        idTable.PrintIdTable("identificators.txt");
        lexTable.PrintLexTable("lexems.txt");


             MFST::Mfst mfst(lexTable, GRB::getGreibach());
        mfst.start();

        mfst.savededucation();

        mfst.printrules();

        translator.transform_data_generator(lexTable, idTable);

        Log::Close(log);
        Out::Close(out);

        //CreateByteCode();
    }
    catch (Error::ERROR e)
    {
        Log::WriteError(log, e);
        Out::WriteError(out, e);
    }
    return 0;
}
