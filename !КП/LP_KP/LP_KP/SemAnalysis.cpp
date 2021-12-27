#define _CRT_SECURE_NO_WARNINGS

#include "stdafx.h"

void SemAnalysis(LT::LexTable& lextable, IT::IdTable& idtable)
{
	//отсутствие блока data
	if(lextable.table[0].lexema	!= LEX_DATAELEMENTS) throw ERROR_THROW(143);

	int decl_end = 0;
	while (lextable.table[decl_end].lexema != LEX_RIGHTBRACE)
		decl_end++;

	//проверка на наличие функции major + проверка, является ли она единственной
	bool main_was = false;
	for (int i = decl_end; i < lextable.current_size; i++)
	{
		if (lextable.table[i].lexema == LEX_MAJOR)
		{
			if (main_was)
			{
				throw ERROR_THROW(148);
			}
			else
			{
				main_was = true;
			}

		}
	}
	if (!main_was) throw ERROR_THROW(149);

	//выход за пределы массива
	for (int i = decl_end; i < lextable.current_size; i++)
	{
		if (lextable.table[i].lexema == LEX_LITERAL && lextable.table[i - 2].lexema == LEX_ID && idtable.table[lextable.table[i - 2].idxTI].idtype == IT::IDTYPE::A)
		{
			if(idtable.table[lextable.table[i - 2].idxTI].value.vint.array_size < idtable.table[lextable.table[i].idxTI].value.vint.value + 1)
				throw ERROR_THROW(145);
		}
	}

	//присвоение параметру
	for (int i = decl_end; i < lextable.current_size; i++)
	{
		if (lextable.table[i].lexema == LEX_EQUALS && lextable.table[i - 1].lexema == LEX_ID && idtable.table[lextable.table[i - 1].idxTI].idtype == IT::IDTYPE::P)
		{
			throw ERROR_THROW(146);
		}
	}

	//присвоение переменной значения другого типа
	for (int i = decl_end, str = 0; i < lextable.current_size; i++)
	{
		if (lextable.table[i - 1].lexema == LEX_SEMICOLON)
			str++;

		if (lextable.table[i].lexema == LEX_EQUALS && lextable.table[i - 1].lexema == LEX_ID)
		{
			int id_pos = i - 1;
			while (lextable.table[++i].lexema != LEX_SEMICOLON)
			{
				if (lextable.table[i].lexema == LEX_ID || lextable.table[i].lexema == LEX_LITERAL)
				{
					if (lextable.table[id_pos].idxTI != 0 && idtable.table[lextable.table[id_pos].idxTI].iddatatype != idtable.table[lextable.table[i].idxTI].iddatatype)
						throw ERROR_THROW_IN(147, str, i);
				}
			}
		}
	}

	//совпадение типа функции с типом возвращаемого значения
	for (int i = decl_end, str = 0; i < lextable.current_size; i++)
	{
		if (lextable.table[i].lexema == LEX_RETURN)
		{
			int j = i;
			while (lextable.table[j].lexema != LEX_FUNCTION && lextable.table[j].lexema != LEX_MAJOR)
				j--;
			if (lextable.table[j].lexema == LEX_MAJOR)
				break;
			if (idtable.table[lextable.table[i + 1].idxTI].iddatatype != idtable.table[lextable.table[j + 1].idxTI].iddatatype )
				throw ERROR_THROW(150);
		}
	}

	//совпадение количества передаваемых параметров с принимаемыми
	for (int i = decl_end; i < lextable.current_size; i++)
	{
		if (lextable.table[i].lexema == LEX_ID && idtable.table[lextable.table[i].idxTI].idtype == IT::IDTYPE::PF)
		{
			int function_id = i;
			int pc = 0;
			while (lextable.table[++i].lexema != LEX_RIGHTHESIS)
			{
				if (lextable.table[i].lexema == LEX_ID || lextable.table[i].lexema == LEX_LITERAL)
					pc++;
			}

			if (pc != idtable.table[lextable.table[function_id].idxTI].value.vint.parm_count)
				throw ERROR_THROW(151);

		}
	}

	//деление на 0
	for (int i = decl_end; i < lextable.current_size; i++)
	{
		if (lextable.table[i].lexema == LEX_DIRSLASH && idtable.table[lextable.table[i + 1].idxTI].value.vint.value == 0)
		{
			throw ERROR_THROW(152);
		}
	}
}