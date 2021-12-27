#include "stdafx.h"

void PolishNotation(LT::LexTable& lextable, IT::IdTable& idtable)
{
	int j = 0;
	LT::LexTable NewLexTable = LT::Create(1000);
	for (int i = 0; i < lextable.current_size; i++)
	{
		if (lextable.table[i].lexema == LEX_EQUALS || lextable.table[i].lexema == LEX_RETURN || lextable.table[i].lexema == LEX_PRINT)
		{
			int parm_counter = 0;
			bool is_funcparm = false;
			stack <char> stackOfOperators;

			while (lextable.table[i].lexema != LEX_SEMICOLON)
			{
				if (lextable.table[i].lexema == LEX_ID || lextable.table[i].lexema == LEX_LITERAL)
				{
					if (lextable.table[i].lexema == LEX_ID and lextable.table[i + 1].lexema == LEX_LEFTHESIS)
					{
						LT::Add(NewLexTable, { lextable.table[i].lexema, lextable.table[i].sn, lextable.table[i].idxTI });
						stackOfOperators.push('@');
						is_funcparm = true;
						i++;
						continue;
					}
					else
					{
						if (is_funcparm)
							parm_counter++;
						LT::Add(NewLexTable, { lextable.table[i].lexema, lextable.table[i].sn, lextable.table[i].idxTI });
						i++;
						continue;
					}
				}

				if (lextable.table[i].lexema == LEX_RIGHTHESIS)
				{
					while (stackOfOperators.top() != LEX_LEFTHESIS)
					{
						LT::Add(NewLexTable, { stackOfOperators.top(), lextable.table[i].sn, lextable.table[i].idxTI });
						stackOfOperators.pop();
					}
					stackOfOperators.pop();
					if (stackOfOperators.top() == LEX_STAR || stackOfOperators.top() == LEX_DIRSLASH)
					{
						LT::Add(NewLexTable, { stackOfOperators.top(), lextable.table[i].sn, lextable.table[i].idxTI });
						stackOfOperators.pop();
					}

					else if (stackOfOperators.top() == '@')
					{
						LT::Add(NewLexTable, { stackOfOperators.top(), lextable.table[i].sn, lextable.table[i].idxTI });
						LT::Add(NewLexTable, { (char)(parm_counter + '0'), lextable.table[i].sn, idtable.current_size});
						parm_counter = 0;
						is_funcparm = false;
						stackOfOperators.pop();
					}
					i++;

					continue;
				}

				if (lextable.table[i].lexema == LEX_COMMA)
				{
					i++;
					continue;
				}


				if (lextable.table[i].lexema == LEX_EQUALS || lextable.table[i].lexema == LEX_RIGHT_SQ_BRACE || lextable.table[i].lexema == LEX_LEFT_SQ_BRACE 
					|| lextable.table[i].lexema == LEX_RETURN || lextable.table[i].lexema == LEX_PRINT)
				{
					LT::Add(NewLexTable, { lextable.table[i++].lexema, lextable.table[i].sn, lextable.table[i].idxTI });
					continue;
				}
				
				if (lextable.table[i].lexema == LEX_PLUS && ((lextable.table[i - 1].lexema == LEX_LITERAL && idtable.table[lextable.table[i - 1].idxTI].iddatatype == IT::IDDATATYPE::STR) 
					|| (lextable.table[i - 1].lexema == LEX_ID && idtable.table[lextable.table[i - 1].idxTI].iddatatype == IT::IDDATATYPE::STR)))
				{
					stackOfOperators.push(LEX_CONCAT);
					i++;
					continue;
				}

				if ((lextable.table[i].lexema == LEX_PLUS || lextable.table[i].lexema == LEX_MINUS) && !stackOfOperators.empty())
				{
					while (!stackOfOperators.empty() && (stackOfOperators.top() == LEX_STAR || stackOfOperators.top() == LEX_DIRSLASH))
					{
						LT::Add(NewLexTable, { stackOfOperators.top(), lextable.table[i].sn, lextable.table[i].idxTI });
						stackOfOperators.pop();
					}
					stackOfOperators.push(lextable.table[i++].lexema);
				}

				else
				{
					stackOfOperators.push(lextable.table[i++].lexema);
				}

			}

			while (!stackOfOperators.empty())
			{
				LT::Add(NewLexTable, { stackOfOperators.top(), lextable.table[i].sn, lextable.table[i].idxTI });
				stackOfOperators.pop();
			}

			LT::Add(NewLexTable, { LEX_SEMICOLON, lextable.table[i].sn, lextable.table[i].idxTI });
		}
		else
		{
			LT::Add(NewLexTable, { lextable.table[i].lexema, lextable.table[i].sn, lextable.table[i].idxTI });
		}
	}
	
	LT::LexTablePrint(NewLexTable);
	generation(NewLexTable, idtable);
}