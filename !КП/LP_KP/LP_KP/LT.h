#pragma once

#include <fstream>

#define	LT_MAXSIZE			10000		// ������������ ���������� ����� � ������� ������	
#define	LT_TI_NULLXDX		0xffffffff	// ��� �������� ������� ���������������	
#define LEX_DATAELEMENTS	'd'			// data elements
#define	LEX_INT				't'			// integer
#define	LEX_STRING			't'			// string
#define LEX_BOOL			't'			// bool
#define LEX_LEFT_SQ_BRACE	'['			// [
#define LEX_RIGHT_SQ_BRACE	']'			// ]
#define LEX_CONCAT			'c'			// ������������ �����
#define	LEX_ID				'i'			// �������������
#define	LEX_LITERAL			'l'			// �������
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
	struct Entry						// ������ ������� ������
	{
		char lexema;					// ������
		int sn;							// ����� ������ � �������� ������
		int idxTI;						// ������ � ������� ��������������� ��� LT_TI_NULLIDX
	};

	struct LexTable						// ��������� ������� ������
	{
		int maxsize;					// ������� ������� ������ < LT_MAXSIZE
		int current_size;				// ������� ������ ������� ������ < maxsize
		Entry* table;					// ������ ����� ������� ������
	};

	LexTable Create(int size);
	void Add(LexTable& lextable, Entry entry);					// ���������� ������
	Entry GetEntry(LexTable& lextable, int n);					// �������� ������ ������� ������
	void Delete(LexTable& lextable);							// ������� ������� ������ (���������� ������)
	void LexTablePrint(LexTable& lextable);
}
