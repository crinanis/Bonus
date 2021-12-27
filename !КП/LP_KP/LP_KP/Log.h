#pragma once
#include "stdafx.h"

using namespace Parm;
using namespace Error;
using namespace In;
using namespace std;

namespace Log
{
	struct LOG
	{
		wchar_t logfile[PARM_MAX_SIZE];
		ofstream* stream;
	};

	static const LOG INITLOG = {L"", NULL};
	LOG getlog(wchar_t logfile[]);
	void WriteLine(LOG log, char* c, ...);
	void WriteLine(LOG log, const wchar_t* c, ...);
	void WriteLog(LOG log);
	void WriteParm(LOG log, PARM parm);
	void WriteIn(LOG log, IN in);
	void WriteError(LOG log, ERROR error);
	void Close(LOG log);
};