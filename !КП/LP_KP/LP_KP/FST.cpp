#include "stdafx.h"

namespace FST
{
	RELATION::RELATION(char transitionSymbol, short newState)
	{
		this->transitionSymbol = transitionSymbol;
		this->nnode = newState;
	}

	NODE::NODE()
	{
		this->relationCounter = 0;
		this->relations = NULL;
	}

	NODE::NODE(short n, RELATION rel, ...)
	{
		this->relationCounter = n;
		this->relations = new RELATION[n];

		RELATION* ptr = &rel;
		for (short i = 0; i < n; i++)
			relations[i] = *ptr++;
	}

	FST::FST(const char* s, short statesCounter, NODE states, ...)
	{
		this->string = s;
		this->statesCounter = statesCounter;
		this->nodes = new NODE[statesCounter];

		NODE* p = &states;
		for (int k = 0; k < statesCounter; k++)
			this->nodes[k] = *p++;

		this->rstates = new short[statesCounter];
		memset(rstates, -1, sizeof(short) * this->statesCounter);
		this->rstates[0] = 0;
		this->position = -1;
	}

	bool step(FST& fst, short* rstates)
	{
		std::swap(rstates, fst.rstates);
		bool rc = false;

		for (short i = 0; i < fst.statesCounter; i++)
		{
			if (rstates[i] == fst.position)
				for (short j = 0; j < fst.nodes[i].relationCounter; j++)
					if (fst.nodes[i].relations[j].transitionSymbol == fst.string[fst.position])
					{
						fst.rstates[fst.nodes[i].relations[j].nnode] = fst.position + 1;
						rc = true;
					}
		}

		return rc;
	}

	bool execute(FST& fst)
	{
		short* rstates = new short[fst.statesCounter];
		memset(rstates, -1, sizeof(short) * fst.statesCounter);
		short lstring = strlen(fst.string);
		bool rc = true;

		for (short i = 0; (i < lstring) && rc; i++)
		{
			fst.position++;
			rc = step(fst, rstates);
		}

		(fst.rstates[fst.statesCounter - 1]) == (lstring) ? rc = true : rc = false;

		return rc;
	}
}