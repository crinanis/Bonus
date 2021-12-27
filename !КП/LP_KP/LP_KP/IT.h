#pragma once


#define IDENT_MAX_SYMBOLS		32				// максимальное количество сиволов в идентификаторе
#define IDENT_MAX_ELEMENTS		4096			// максимальное количество эл-ов в таблице идентификаторов 
#define IDENT_INT_DEFAULT		0x00000000		// значение по умолчанию дл€ типа integer 
#define IDENT_STR_DEFAULT		0x00			// значение по умолчанию дл€ типа string 
#define IDENT_LOG_DEFAULT		0				// значение по умолчанию дл€ типа bool
#define IDENT_NULLIDX			0xffffffff		// нет элемента таблицы идентификаторов
#define IDENT_STR_MAXSIZE		255				// максимальна€ длинна строки
#define IDENT_ARRAY_MAXSIZE		10				// максимальный размер массива

namespace IT
{
	enum IDDATATYPE { INT = 1, STR = 2, BOO = 3};				// типы данных идентификаторов: integer, string
	enum IDTYPE { V = 1, F = 2, P = 3, L = 4, PF = 5, A = 6};	// типы идентификаторов: переменна€, функци€, параметр, литерал, прототип функции, массив

	struct Entry		// строка таблицы идентификаторов
	{
		int				idxLT;
		char			parrent_block_name[IDENT_MAX_SYMBOLS];	// им€ родительского блока
		char			id[IDENT_MAX_SYMBOLS];					// идентификатор (автоматически усекаетс€ до ID_MAXSIZE)
		IDDATATYPE		iddatatype;						// тип данных
		IDTYPE			idtype;							// тип идентификатора

		union
		{
			struct
			{
				int value;
				int array_size;
				int parm_count;
			}vint;						// значение integer
			struct
			{
				char len;						// количесво символов в string
				char str[IDENT_STR_MAXSIZE - 1];	// символы string
			} vstr[IDENT_STR_MAXSIZE];				// значение string
			bool vlogic;
		} value;								// значение идентификатора
	};

	struct IdTable // экземпл€р таблицы идентификаторов
	{
		int maxsize;				// емкость таблицы идентификаторов < IDENT_MAX_ELEMENTS
		int current_size;			// текущий размер таблицы идентификаторов < maxsize
		Entry* table;				// массив строк таблицы идентификаторов
	};

	IdTable Create(int size);
	void Add(IdTable& idtable, Entry entry);
	Entry GetEntry(IdTable& idtable, int n);
	int IsId(IdTable& idtable, char id[IDENT_MAX_SYMBOLS]);
	void Delete(IdTable& idtable);
	void PrintIdTable(IdTable& idtable);
};