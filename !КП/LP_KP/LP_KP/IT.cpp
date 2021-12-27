#include "stdafx.h"

namespace IT
{
	IdTable Create(int size)
	{
		IdTable idtable;
		idtable.maxsize = size;
		idtable.current_size = 0;
		idtable.table = new Entry[IDENT_MAX_ELEMENTS];
		if (size > IDENT_MAX_ELEMENTS) throw ERROR_THROW(125);
		return idtable;
	}

	Entry GetEntry(IdTable& idtable, int n)
	{
		if (n < idtable.maxsize && n >= 0)
			return idtable.table[n];
		else
			throw ERROR_THROW(128)
	}

	void Delete(IdTable& idtable)
	{
		delete idtable.table;
		idtable.table = nullptr;
	}

	void Add(IdTable& idtable, Entry entry)
	{
		if (strlen(entry.id) > IDENT_MAX_SYMBOLS)
			throw ERROR_THROW(136);

		if (idtable.current_size < idtable.maxsize)
		{
			idtable.table[idtable.current_size] = entry;

			if (entry.iddatatype == IT::IDDATATYPE::INT)
				idtable.table[idtable.current_size].value.vint.value = IDENT_INT_DEFAULT;

			if (entry.iddatatype == IT::IDDATATYPE::STR)
			{
				idtable.table[idtable.current_size].value.vstr->str[0] = IDENT_STR_DEFAULT;
				idtable.table[idtable.current_size].value.vstr->len = 0;
			}

			if (entry.iddatatype == IT::IDDATATYPE::BOO)
				idtable.table[idtable.current_size].value.vlogic = IDENT_LOG_DEFAULT;

			idtable.current_size++;
		}
		else
			throw ERROR_THROW(125);
	}

	int IsId(IdTable& idtable, char id[IDENT_MAX_SYMBOLS])
	{
		for (int i = 0; i < idtable.current_size; i++)
		{
			if (strcmp(idtable.table[i].id, id) == 0)
				return i;
		}
		return IDENT_NULLIDX;
	}

	void PrintIdTable(IdTable& idtable)
	{
		ofstream fout("TableOfIdentificators.txt");

		if (fout.is_open())
		{
			fout << "Литералы: \n\n";

			for (int i = 0; i < idtable.current_size; i++)
			{
				if (idtable.table[i].idtype == IT::IDTYPE::L)
				{
					if (idtable.table[i].iddatatype == INT)
					{
						fout << "int" << setw(40 - 7) << idtable.table[i].value.vint.value << endl;
					}
					else if(idtable.table[i].iddatatype == IDDATATYPE::STR)
					{
						fout << "string" << setw(40 - 6) << idtable.table[i].value.vstr->str << "\t\t" << (int)idtable.table[i].value.vstr->len << std::endl;
					}
					else
					{
						fout << "bool" << setw(40 - 5) << idtable.table[i].value.vlogic << std::endl;
					}
				}
			}
			fout << "\n\n\n";

			fout << "Функции: \n\n";

			for (int i = 0; i < idtable.current_size; i++)
			{
				if (idtable.table[i].idtype == IT::IDTYPE::F)
				{
					if (idtable.table[i].iddatatype == IDDATATYPE::INT)
					{
						fout << idtable.table[i].id << setw(40 - strlen(idtable.table[i].id)) << "int" << endl;
					}
					else if (idtable.table[i].iddatatype == IDDATATYPE::STR)
					{
						fout << idtable.table[i].id << setw(40 - strlen(idtable.table[i].id)) << "string" << std::endl;
					}
					else
					{
						fout << idtable.table[i].id << setw(40 - strlen(idtable.table[i].id)) << "bool" << std::endl;
					}
				}


			}
			fout << "\n\n\n";

			fout << "Переменные: \n\n";

			for (int i = 0; i < idtable.current_size; i++)
			{
				if (idtable.table[i].idtype == IT::IDTYPE::V)
				{
					if (idtable.table[i].iddatatype == IDDATATYPE::INT)
					{
						fout << idtable.table[i].parrent_block_name << setw(40 - strlen(idtable.table[i].parrent_block_name)) << idtable.table[i].id << setw(40 - strlen(idtable.table[i].id)) << "int\tV" << setw(10) << idtable.table[i].value.vint. value << endl;
					}
					else if(idtable.table[i].iddatatype == IDDATATYPE::STR)
					{
						fout << idtable.table[i].parrent_block_name << setw(40 - strlen(idtable.table[i].parrent_block_name)) << idtable.table[i].id << setw(40 - strlen(idtable.table[i].id))  << "string\tV" << setw(10) << idtable.table[i].value.vstr->str << setw(10) << idtable.table[i].value.vstr->len <<  endl;
					}
					else
					{
						fout << idtable.table[i].parrent_block_name << setw(40 - strlen(idtable.table[i].parrent_block_name)) << idtable.table[i].id << setw(40 - strlen(idtable.table[i].id))  << "bool\tV" << setw(10) << idtable.table[i].value.vlogic << endl;
					}
				}

				if (idtable.table[i].idtype == IT::IDTYPE::P)
				{
					if (idtable.table[i].iddatatype == IDDATATYPE::INT)
					{
						fout << idtable.table[i].parrent_block_name << setw(40  - strlen(idtable.table[i].parrent_block_name)) << idtable.table[i].id << setw(40 - strlen(idtable.table[i].id))  << "int\tP" << setw(10) << idtable.table[i].value.vint.value << endl;
					}
					else if (idtable.table[i].iddatatype == IDDATATYPE::STR)
					{
						fout << idtable.table[i].parrent_block_name << setw(40  - strlen(idtable.table[i].parrent_block_name)) << idtable.table[i].id << setw(40 - strlen(idtable.table[i].id))  << "string\tP" << setw(10) << idtable.table[i].value.vstr->str << setw(10) << idtable.table[i].value.vstr->len << endl;
					}
					else
					{
						fout << idtable.table[i].parrent_block_name << setw(40  - strlen(idtable.table[i].parrent_block_name)) << idtable.table[i].id << setw(40 - strlen(idtable.table[i].id))  << "bool\tP" << setw(10) << idtable.table[i].value.vlogic << endl;
					}
				}

				if (idtable.table[i].idtype == IT::IDTYPE::A)
				{
					if (idtable.table[i].iddatatype == IDDATATYPE::INT)
					{
						fout << idtable.table[i].parrent_block_name << setw(40 - strlen(idtable.table[i].parrent_block_name)) << idtable.table[i].id << setw(40 - 7) << "int\tA"  << endl;
					}
					else if (idtable.table[i].iddatatype == IDDATATYPE::STR)
					{
						fout << idtable.table[i].parrent_block_name << setw(40 - strlen(idtable.table[i].parrent_block_name)) << idtable.table[i].id << setw(40 - 6) << "string\tA"  << endl;
					}
					else
					{
						fout << idtable.table[i].parrent_block_name << setw(40 - strlen(idtable.table[i].parrent_block_name)) << idtable.table[i].id << setw(40 - 6) << "bool\tA"  << endl;
					}
				}
			}
			fout << "\n\n\n";
		}
		else
			throw ERROR_THROW(127);
		fout.close();
	}
}

