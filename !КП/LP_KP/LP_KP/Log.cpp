#include "stdafx.h"

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)

using namespace Parm;
using namespace Error;
using namespace In;
using namespace std;
using namespace Log;

Log::LOG Log::getlog(wchar_t logfile[])
{
	Log::LOG tmp;
	tmp.stream = new std::ofstream;
	tmp.stream->open(logfile);
	if (!tmp.stream->is_open()) {
		throw ERROR_THROW(112);
	}
	wcscpy_s(tmp.logfile, logfile);
	return tmp;
}

void Log::WriteLine(LOG log, char* c, ...)
{
	std::string str;
	va_list args;
	va_start(args, c);
	char* i = c;
	str += i;
	while ((i = va_arg(args, char*)) != "")
	{
		str += i;
	}
	va_end(args);
	*log.stream << str << '\n';
	log.stream->flush();
}

void Log::WriteLine(LOG log, const wchar_t* c, ...)
{
	const wchar_t** ptr = &c;

	char temp[100];

	while (*ptr != L"")
	{
		wcstombs(temp, *ptr++, sizeof(temp));
		*log.stream << temp;
		++ptr;
	}
	log.stream->flush();
}

void Log::WriteLog(LOG log)
{
	*log.stream << "------- Протокол ------ : ";
	time_t now = time(0);
	tm date;
	localtime_s(&date, &now);
	char buf[228];
	strftime(buf, sizeof(buf), "%c", &date);
	*log.stream << buf << "------\n";
	log.stream->flush();
}

void Log::WriteParm(LOG log, Parm::PARM parm)
{
	char str[255];

	*log.stream << "----- Параметры -----\n";

	wcstombs(str, parm.in, wcslen(parm.in));
	str[wcslen(parm.in)] = '\0';
	*log.stream << "-in: ";
	log.stream->write(str, strlen(str)) << "\n";

	wcstombs(str, parm.out, wcslen(parm.out));
	str[wcslen(parm.out)] = '\0';
	*log.stream << "-out: ";
	log.stream->write(str, strlen(str)) << "\n";

	wcstombs(str, parm.log, wcslen(parm.log));
	str[wcslen(parm.log)] = '\0';
	*log.stream << "-log: ";
	log.stream->write(str, strlen(str)) << "\n";
	log.stream->flush();
}

void Log::WriteIn(LOG log, In::IN in)
{
	*log.stream << "----- Исходные данные -----";
	*log.stream << "\nРазмер : " << in.size;
	*log.stream << "\nИгнорированные: " << in.ignor;
	*log.stream << "\nСтроки    : " << in.lines + 1;
	log.stream->flush();
}

void Log::WriteError(LOG log, Error::ERROR error)
{
	if (log.stream != NULL)
	{
		*log.stream << "\nОшибка " << error.id << ": " << error.message << ", строка " << error.inext.line + 1 << " символ " << error.inext.col;
	}
	else
	{
		std::cout << "\nОшибка " << error.id << ": " << error.message << ", строка " << error.inext.line + 1 << " символ " << error.inext.col << endl;
	}

}

void Log::Close(LOG log)
{
	log.stream->close();
}