#pragma once

#include "stdafx.h"

#define STANDART_BEGIN    ".586							; система команд (процессор Pentium)\n"						\
					   << ".model flat, stdcall			; модель памяти, соглашение о вызовах\n"					\
					   << "includelib kernel32.lib			; компановщику: компоновать с kernel32\n"				\
					   << "includelib libucrt.lib			; для UCRT - universal C Run-Time library\n\n"			\
					   << "ExitProcess PROTO: DWORD		; прототип функции для завершения процесса Windows\n\n"		\

#define STANDART_LIB	  ";-----------Standart functions-----------\n"					\
					   << "includelib e:\\!ПОИТ\\2\\First\\ЯП\\КП\\LP_KP\\Debug\\StandartLibrary.lib\n"	\
					   << "cat1 PROTO : DWORD, : DWORD\n"							\
					   << "cat2 PROTO : DWORD, : DWORD, : DWORD\n"					\
					   << "print PROTO : DWORD\n"										\
					   << "printint PROTO : DWORD\n"									\
					   << "isleap PROTO : DWORD\n"								\
					   << "printcurrentdate PROTO\n"									\
					   << ";----------------------------------------\n\n";	

#define STACK(value) ".stack " << value << "\n\n";

#define LITERALS_BEGIN ";---------------Literals---------------\n"\
								<< ".const\n\n";

#define LITERALS_END	 ";--------------------------------------------\n";

#define VARIABLES_BEGIN "\n\n;----------------Variables-------------------\n.data\n\n";

#define VARIABLES_END	 ";--------------------------------------------\n";

#define FUNCTIONS_BEGIN "\n;----------------Functions-------------------\n\n"\
						<< ".code\n\n";

#define FUNCTIONS_END	"\n;----------------------------------------------\n";




	void generation(LT::LexTable& LexTable, IT::IdTable& IdTable);

