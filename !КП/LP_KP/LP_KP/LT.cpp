#include "stdafx.h"

namespace LT 
{
	LexTable Create(int size)
	{
		LT::LexTable lextable;
		lextable.maxsize = size;
		lextable.current_size = 0;
		lextable.table = new LT::Entry[size];
		if (size > LT_MAXSIZE) throw ERROR_THROW(122);
		return lextable;
		
	}

	void Add(LexTable& lextable, Entry entry)
	{
		if (lextable.current_size < lextable.maxsize)
		{
			lextable.table[lextable.current_size] = entry;
			lextable.current_size++;
		}
		else
			throw ERROR_THROW(122);
	}

	Entry GetEntry(LexTable& lextable, int n)
	{
		if (n < lextable.maxsize && n >= 0)
			return lextable.table[n];
		else
			throw ERROR_THROW(122);
	}

	void Delete(LexTable& lextable)
	{
		delete lextable.table;
		lextable.table = nullptr;
	}

	void LexTablePrint(LexTable& lextable)
	{
		ofstream fout("TableOfLexems.txt");
		int current_string = 0;
		fout << current_string + 1 << '\t';
		for (int i = 0; i < lextable.current_size; i++)
		{
			if (current_string != lextable.table[i].sn)
			{
				current_string = lextable.table[i].sn;
				fout << endl << lextable.table[i].sn + 1 << '\t';
			}
			fout << lextable.table[i].lexema;
		}
		fout.close();
	}
}


