#pragma once

#include <fstream>

#define	LT_MAXSIZE			10000		// максимальное количество строк в таблице лексем	
#define	LT_TI_NULLXDX		0xffffffff	// нет элемента таблицы идентификаторов	
#define LEX_DATAELEMENTS	'd'			// data elements
#define	LEX_INT				't'			// integer
#define	LEX_STRING			't'			// string
#define LEX_BOOL			't'			// bool
#define LEX_LEFT_SQ_BRACE	'['			// [
#define LEX_RIGHT_SQ_BRACE	']'			// ]
#define LEX_CONCAT			'c'			// конкатенация строк
#define	LEX_ID				'i'			// идентификатор
#define	LEX_LITERAL			'l'			// литерал
#define	LEX_FUNCTION		'f'			// function
#define	LEX_RETURN			'r'			// return
#define	LEX_PRINT			'p'			// print
#define LEX_MAJOR			'm'			// major
#define LEX_EQUALS			'e'			// equals
#define LEX_TRUE			'T'			// true
#define LEX_FALSE			'F'			// false
#define LEX_CONDITION		'I'			// if
#define LEX_REFERENSE		'$'         // $
#define LEX_WHILE			'w'			// while
#define	LEX_SEMICOLON		';'			// ;
#define	LEX_COMMA			','			// ,
#define	LEX_LEFTBRACE		'{'			// {
#define	LEX_RIGHTBRACE		'}'			// }
#define	LEX_LEFTHESIS		'('			// (
#define	LEX_RIGHTHESIS		')'			// )
#define	LEX_PLUS			'+'			// +
#define	LEX_MINUS			'-'			// -
#define	LEX_STAR			'*'			// *
#define	LEX_DIRSLASH		'%'			// /
#define	LEX_EQUAL_SIGN		'='			// =
#define LEX_MORE			'>'			// >
#define LEX_LESS			'<'			// <
#define LEX_MORE_OR_EQUAL	'/'			// >=
#define LEX_LESS_OR_EQUAL	'b'			// <=



namespace LT
{
	struct Entry						// строка таблицы лексем
	{
		char lexema;					// лесема
		int sn;							// номер строки в исходном тексте
		int idxTI;						// индекс в таблице идентификаторов или LT_TI_NULLIDX
	};

	struct LexTable						// экземпляр таблицы лексем
	{
		int maxsize;					// емкость таблицы лексем < LT_MAXSIZE
		int current_size;				// текущий размер таблицы лексем < maxsize
		Entry* table;					// массив строк таблицы лексем
	};

	LexTable Create(int size);
	void Add(LexTable& lextable, Entry entry);					// добавление лексем
	Entry GetEntry(LexTable& lextable, int n);					// получить строку таблицы лексем
	void Delete(LexTable& lextable);							// удалить таблицу лексем (освободить память)
	void LexTablePrint(LexTable& lextable);
}
