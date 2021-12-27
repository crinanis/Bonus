#include "stdafx.h"

#define GRB_ERROR_SERIES 130

namespace GRB
{
	#define NS(n) Rule::Chain::N(n)
	#define TS(n) Rule::Chain::T(n)

	Rule::Chain::Chain(short symbolCount, GRBALPHABET s, ...)
	{
		this->chainOfTerm_nTerm = new GRBALPHABET[this->size = symbolCount];

		int* ptr = (int*)&s;
		for (int i = 0; i < symbolCount; i++)
			this->chainOfTerm_nTerm[i] = (short)ptr[i];
	}

	Rule::Rule(GRBALPHABET pnn, int piderror, short psize, Chain c, ...)
	{
		this->nn = pnn;
		this->iderror = piderror;
		this->chains = new Chain[this->size = psize];

		Chain* p = &c;
		for (int i = 0; i < size; i++)
			this->chains[i] = p[i];
	}

	Greibach::Greibach(GRBALPHABET pstartN, GRBALPHABET pstbottom, short psize, Rule r, ...)
	{
		this->startN = pstartN;
		this->stbottomT = pstbottom;
		this->rules = new Rule[this->size = psize];
		Rule* p = &r;
		for (int i = 0; i < size; i++)
			rules[i] = p[i];
	}

	short Greibach::getRule(GRBALPHABET pnn, Rule& prule)
	{
		short rc = -1, k = 0;
		while (k < this->size && rules[k].nn != pnn)
			k++;
		if (k < this->size)
			prule = rules[rc = k];

		return rc;
	}

	Rule Greibach::getRule(short n)
	{
		Rule rc;
		if (n < this->size)
			rc = rules[n];
		return rc;
	}

	char* Rule::getCRule(char* b, short nchain)
	{
		char bchain[200];
		b[0] = Chain::alphabet_to_char(this->nn);
		b[1] = '-';
		b[2] = '>';
		b[3] = 0x00;
		this->chains[nchain].getCChain(bchain);
		strcat_s(b, sizeof(bchain) + 5, bchain);
		return b;
	}

	short Rule::getNextChain(GRBALPHABET t, Rule::Chain& pchain, short j)
	{
		short rc = -1;

		while (j < this->size && this->chains[j].chainOfTerm_nTerm[0] != t)
			++j;
		rc = (j < this->size ? j : -1);
		if (rc >= 0)
			pchain = chains[rc];
		return rc;
	}

	char* Rule::Chain::getCChain(char* b)
	{
		for (int i = 0; i < this->size; i++)
			b[i] = Chain::alphabet_to_char(this->chainOfTerm_nTerm[i]);
		b[this->size] = 0x00;
		return b;
	}

	Greibach greibach(
		NS('S'), TS('$'), // стартовый символ, дно стека
		10,

		Rule(NS('S'), GRB_ERROR_SERIES + 0, // неверна€ структура программы
			4,		// S-> m{NrE;} | d{N}S | tfi(F){NrE;}S | m{NrE;}S | tfi(F){NrE;} | tfi(F){rE;}
			
			//функци€ major
			Rule::Chain(7, TS('m'), TS('{'), NS('N'), TS('r'), NS('B'), TS(';'), TS('}')),

			//блок data
			Rule::Chain(5, TS('d'), TS('{'), NS('N'), TS('}'), NS('S')),

			//реализаци€ функций с параметрами
			Rule::Chain(13, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('r'), NS('B'), TS(';'), TS('}'), NS('S')),

			//реализаци€ функций без параметров
			Rule::Chain(12, TS('t'), TS('f'), TS('i'), TS('('), TS(')'), TS('{'), NS('N'), TS('r'), NS('B'), TS(';'), TS('}'), NS('S'))
		),

		Rule(NS('N'), GRB_ERROR_SERIES + 1, // ошибочный сепаратор
			
			27,		// N-> dti; | rE; | i=E; | tfi(F); | ti;N | rE;N | i=E;N | tfi(F);N | pE; | pE;N | t[l]i;N | I(E){N}N | I(E){N} | w(E){N}N | w(E){N}

			Rule::Chain(6, TS('i'), TS('('), NS('W'), TS(')'), TS(';'), NS('N')),
			Rule::Chain(4, TS('i'), TS('('), NS('W'), TS(')')),
			Rule::Chain(3, TS('i'), TS('('), TS(')')),

			//объ€вление переменных,функций,массивов
			Rule::Chain(4, TS('t'), TS('i'), TS(';'), NS('N')),
			Rule::Chain(3, TS('t'), TS('i'), TS(';')),
			Rule::Chain(7, TS('t'), TS('$'), TS('i'), TS('$'), TS('i'), TS(';'), NS('N')),
			Rule::Chain(6, TS('t'), TS('$'), TS('i'), TS('$'), TS('i'), TS(';')),
			Rule::Chain(8, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS(';'), NS('N')),
			Rule::Chain(7, TS('t'), TS('f'), TS('i'), TS('('), TS(')'), TS(';'), NS('N')),
			Rule::Chain(7, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS(';')),
			Rule::Chain(7, TS('t'), TS('f'), TS('i'), TS('('), TS(')'), TS(';')),
			Rule::Chain(8, TS('t'), TS('['), TS('l'), TS(']'), TS('i'), NS('L'), TS(';'), NS('N')),
			Rule::Chain(6, TS('t'), TS('['), TS('l'), TS(']'), TS('i'), NS('L'), TS(';')),
			Rule::Chain(10, TS('t'), TS('$'), TS('i'), TS('$'), TS('['), NS('L'), TS(']'), TS('i'), TS(';'), NS('N')),
			Rule::Chain(9, TS('t'), TS('$'), TS('i'), TS('$'), TS('['), NS('L'), TS(']'), TS('i'), TS(';')),
			

			//иницализаци€ переменных
			Rule::Chain(5, TS('i'), TS('e'), NS('E'), TS(';'), NS('N')),
			Rule::Chain(4, TS('i'), TS('e'), NS('E'), TS(';')),
			
			//вывести в консоль выражение
			Rule::Chain(4, TS('p'), NS('B'), TS(';'), NS('N')),
			Rule::Chain(3, TS('p'), NS('B'), TS(';')),

			//условный блок
			Rule::Chain(8, TS('I'), TS('('), NS('C'), TS(')'), TS('{'), NS('N'), TS('}'), NS('N')),
			Rule::Chain(7, TS('I'), TS('('), NS('C'), TS(')'), TS('{'), NS('N'), TS('}')),
			Rule::Chain(10, TS('I'), TS('('), NS('C'), TS(')'), TS('{'), TS('r'), NS('E'), TS(';'), TS('}'), NS('N')),
			Rule::Chain(9, TS('I'), TS('('), NS('C'), TS(')'), TS('{'), TS('r'), NS('E'), TS(';'), TS('}')),
			Rule::Chain(11, TS('I'), TS('('), NS('C'), TS(')'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), NS('N')),
			Rule::Chain(10, TS('I'), TS('('), NS('C'), TS(')'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}')),

			//цикл
			Rule::Chain(8, TS('w'), TS('('), NS('C'), TS(')'), TS('{'), NS('N'), TS('}'), NS('N')),
			Rule::Chain(7, TS('w'), TS('('), NS('C'), TS(')'), TS('{'), NS('N'), TS('}'))
		),

		Rule(NS('E'), GRB_ERROR_SERIES + 2, // ошибка в выражении
			13,  // E-> i| l | (E) | i(W) | iM | lM | (E)M | i(W)M
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(4, TS('i'), TS('['), TS('l'), TS(']')),
			Rule::Chain(4, TS('i'), TS('['), TS('i'), TS(']')),
			Rule::Chain(5, TS('i'), TS('['), TS('l'), TS(']'), NS('M')),
			Rule::Chain(5, TS('i'), TS('['), TS('i'), TS(']'), NS('M')),
			Rule::Chain(3, TS('('), NS('E'), TS(')')),
			Rule::Chain(4, TS('i'), TS('('), NS('W'), TS(')')),
			Rule::Chain(5, TS('i'), TS('('), NS('W'), TS(')'), NS('M')),
			Rule::Chain(3, TS('i'), TS('('), TS(')')),
			Rule::Chain(2, TS('i'), NS('M')),
			Rule::Chain(2, TS('l'), NS('M')),
			Rule::Chain(4, TS('('), NS('E'), TS(')'), NS('M'))
			
		),

		Rule(NS('L'), GRB_ERROR_SERIES + 1, //операнд в выражении
			2,
			Rule::Chain(1, TS('l')),
			Rule::Chain(3, TS('l'), TS(','), NS('L'))
		),

		Rule(NS('B'), GRB_ERROR_SERIES + 1, //операнд в выражении
			4,	
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(4, TS('i'), TS('['), TS('i'), TS(']')),
			Rule::Chain(4, TS('i'), TS('['), TS('l'), TS(']'))
		),

		Rule(NS('M'), GRB_ERROR_SERIES + 2,	// ошибка в выражении
			8,	// M-> vE | vEM

			Rule::Chain(2, TS('+'), NS('E')),
			Rule::Chain(2, TS('-'), NS('E')),
			Rule::Chain(2, TS('*'), NS('E')),
			Rule::Chain(2, TS('%'), NS('E')),
		
			Rule::Chain(3, TS('+'), NS('E'), NS('M')),
			Rule::Chain(3, TS('-'), NS('E'), NS('M')),
			Rule::Chain(3, TS('*'), NS('E'), NS('M')),
			Rule::Chain(2, TS('%'), NS('E'), NS('M'))

		),

		Rule(NS('C'), GRB_ERROR_SERIES + 5, 
			2,	//условие входа в блок
			Rule::Chain(3, TS('i'), NS('O'), NS('B')),
			Rule::Chain(3, TS('l'), NS('O'), NS('B'))
		),

		Rule(NS('O'), GRB_ERROR_SERIES + 5, 
			5,	//оператор в условии входа в блок
			Rule::Chain(1, TS('<')),
			Rule::Chain(1, TS('>')),
			Rule::Chain(1, TS('/')),
			Rule::Chain(1, TS('b')),
			Rule::Chain(1, TS('='))
		),

		Rule(NS('F'), GRB_ERROR_SERIES + 3,		// ошибка в параметрах функции
			2,	// F-> ti | ti,F
			Rule::Chain(2, TS('t'), TS('i')),
			Rule::Chain(4, TS('t'), TS('i'), TS(','), NS('F'))
		),

		Rule(NS('W'), GRB_ERROR_SERIES + 4,	// ошибка в параметрах вызываемой функции
			4,	// W-> i | l | i,W | l,W
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(3, TS('i'), TS(','), NS('W')),
			Rule::Chain(3, TS('l'), TS(','), NS('W'))
		)
	);

	Greibach getGreibach()
	{
		return greibach;
	}
}