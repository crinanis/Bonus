#include "stdafx.h"

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)

Parm::PARM Parm::getParm(int argc, _TCHAR* argv[])
{
	PARM element;
	bool is_in_param = false;

	for (int i = 1; i < argc; i++)
		if (wcslen(argv[i]) > PARM_MAX_SIZE)
			throw ERROR_THROW(104);
	if (argv[1] != NULL)
	{
		if (wcsstr(argv[1], PARM_IN) != NULL)
		{
			wcscpy(element.in, wcsstr(argv[1], wcschr(argv[1], L':') + 1));

			for (int i = 1; i < argc; i++)
			{
				if (wcsstr(argv[i], PARM_OUT) != NULL)
					wcscpy(element.out, wcsstr(argv[i], wcschr(argv[i], L':')));
				else
					wcscpy(element.out, wcscat(element.in, PARM_OUT_DEFAULT_EXT));
			}

			wcscpy(element.in, wcsstr(argv[1], wcschr(argv[1], L':') + 1));

			for (int i = 1; i < argc; i++)
			{
				if (wcsstr(argv[i], PARM_LOG) != NULL)
					wcscpy(element.log, wcsstr(argv[i], wcschr(argv[i], L':')));
				else
					wcscpy(element.log, wcscat(element.in, PARM_LOG_DEFAULT_EXT));
			}

			wcscpy(element.in, wcsstr(argv[1], wcschr(argv[1], L':') + 1));
		}
	}
	else
		throw ERROR_THROW(100);

	return element;
}