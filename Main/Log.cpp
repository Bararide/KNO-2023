
#include "Log.h"

namespace Log 
{
	LOG getlog(char logfile[])
	{
		LOG log;
		log.stream = new ofstream;
		log.stream->open(logfile);
		if (log.stream->fail())
			throw ERROR_THROW(112);
		strcpy(log.logfile, logfile);
		return log;
	}

	void WriteLine(LOG log, const char* c)
	{
		*log.stream << c;
		*log.stream << endl;
	}

	void WriteLog(LOG log) 
	{
		char date[100];
		time_t local = time(nullptr);
		struct tm* currentTime;
		currentTime = localtime(&local);
		strftime(date, 100, "%d.%m.%Y %H:%M:%S", currentTime);
		*log.stream << "--- Протокол --- " << date << endl;
	}
	void WriteParm(LOG log, Parm::PARM parm) 
	{
		*log.stream << "--- Параметры --- " << endl;
		*log.stream << "-in : " << parm.in << endl;
		*log.stream << "-out: " << parm.out << endl;
		*log.stream << "-log: " << parm.log << endl;
	}
	void WriteIn(LOG log, In::IN in) {

		*log.stream << "--- Исходные данные --- " << endl;
		*log.stream << "Количество символов : " << in.size << endl;
		*log.stream << "Количество строк    : " << in.lines << endl;
		*log.stream << "Проигнорировано     : " << in.ignor << endl;
	}
	void WriteError(LOG log, Error::ERROR error) 
	{
		if (log.stream)
		{
			*log.stream << "--- Ошибка!!! --- " << endl;
			*log.stream << "Ошибка " << error.id << ": " << error.message << endl;
			if (error.inext.line != -1)
			{
				*log.stream << "Строка: " << error.inext.line << endl << "Столбец: " << error.inext.col << endl << endl;
			}
		}
		else
			cout << "Ошибка " << error.id << ": " << error.message << ", строка " << error.inext.line << ", позиция " << error.inext.col << endl << endl;
	}
	void Close(LOG log) {
		log.stream->close();
		delete log.stream;
	}
}