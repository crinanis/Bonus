#include "stdafx.h"

namespace Error
{
	ERROR errors[ERROR_MAX_ENTRY] =
	{
		ERROR_ENTRY(0, "������������ ��� ������"),
		ERROR_ENTRY(1, "��������� ����"),
		ERROR_ENTRY_NODEF(2),ERROR_ENTRY_NODEF(3),ERROR_ENTRY_NODEF(4),ERROR_ENTRY_NODEF(5),ERROR_ENTRY_NODEF(6),ERROR_ENTRY_NODEF(7),ERROR_ENTRY_NODEF(8),ERROR_ENTRY_NODEF(9),
		ERROR_ENTRY_NODEF10(10),ERROR_ENTRY_NODEF10(20),ERROR_ENTRY_NODEF10(30),ERROR_ENTRY_NODEF10(40),ERROR_ENTRY_NODEF10(50),ERROR_ENTRY_NODEF10(60),ERROR_ENTRY_NODEF10(70),
		ERROR_ENTRY_NODEF10(80),ERROR_ENTRY_NODEF10(90),
		ERROR_ENTRY(100, "Parm: �������� -in ������ ���� �����"),
		ERROR_ENTRY_NODEF(101),ERROR_ENTRY_NODEF(102),ERROR_ENTRY_NODEF(103),
		ERROR_ENTRY(104, "Parm: ��������� ����� �������� ���������"),
		ERROR_ENTRY_NODEF(105),ERROR_ENTRY_NODEF(106),ERROR_ENTRY_NODEF(107),ERROR_ENTRY_NODEF(108),ERROR_ENTRY_NODEF(109),
		ERROR_ENTRY(110, "In: ������ ��� �������� ����� � �������� ����� (-in)"),
		ERROR_ENTRY(111, "In: ������������ ������ � �������� ����� (-in)"),
		ERROR_ENTRY(112, "Log: ������ ��� �������� ����� ��������� (-log)"),
		ERROR_ENTRY(113, "Code generation: ������ ��� �������� ����� ���������� (asm)"),ERROR_ENTRY_NODEF(114),ERROR_ENTRY_NODEF(115),ERROR_ENTRY_NODEF(116),ERROR_ENTRY_NODEF(117),ERROR_ENTRY_NODEF(118),ERROR_ENTRY_NODEF(119),

		ERROR_ENTRY(120, "Lex analysis: �������������� �������"),
		ERROR_ENTRY(121, "Lex analysis: ��������� ������������ ����� ���������� ��������"),
		ERROR_ENTRY(122, "LT: �������� ������������ ������ ������� ������"),
		ERROR_ENTRY(123, "Lex analysis: ��������������� �������������� �������"),
		ERROR_ENTRY(124, "Lex analysis: �� ������� ���������� �����"),
		ERROR_ENTRY(125, "IT: ������������ ������� ���������������"),
		ERROR_ENTRY(126, "Lex analysis: ��������������� ������������� ��������������"),
		ERROR_ENTRY(127, "IT: ������ � �������� ����� � �������� ���������������"),
		ERROR_ENTRY(128, "IT: �������� ������������ ������ ������� ���������������"),
		ERROR_ENTRY(129, "Lex analysis: ����������� ����������"),

		ERROR_ENTRY(130, "Synt analysis: �������� ��������� ���������"),
		ERROR_ENTRY(131, "Synt analysis: ��������� ���������"),
		ERROR_ENTRY(132, "Synt analysis: ������ � ���������"),
		ERROR_ENTRY(133, "Synt analysis: ������ � ���������� �������"),
		ERROR_ENTRY(134, "Synt analysis: ������ � ���������� ���������� �������"),
		ERROR_ENTRY(135, "Synt analysis: �������� ������� ����� � ����"),
		ERROR_ENTRY(136, "IT: �������� ������������ ������ ��������������"),
		ERROR_ENTRY_NODEF(137),
		ERROR_ENTRY_NODEF(138),
		ERROR_ENTRY_NODEF(139),
		ERROR_ENTRY_NODEF(140),
		ERROR_ENTRY(141, "Lex analysis: ���������� ������� ��������� ������"),
		ERROR_ENTRY(142, "Lex analysis: ���������� ������� ������� ������"),
		ERROR_ENTRY(143, "Sem analysis: ����������� ���� ���������� data"),
		ERROR_ENTRY(144, "Lex analysis: ��������� ���������� �������� ��������"),
		ERROR_ENTRY(145, "Sem analysis: ����� �������� �� ������� �������"),
		ERROR_ENTRY(146, "Sem analysis: ������� ��������� �������� ���������"),
		ERROR_ENTRY(147, "Sem analysis: ��� ����������� �������� �� ��������� � ����������-���������"),
		ERROR_ENTRY(148, "Sem analysis: ������� major ������ ���� ������������"),
		ERROR_ENTRY(149, "Sem analysis: ����������� ������� major"),
		ERROR_ENTRY(150, "Sem analysis: ��� ������� � ��� ������������� �������� �� ���������"),
		ERROR_ENTRY(151, "Sem analysis: ���������� ������������ � ����������� ���������� �� ���������"),
	/*	ERROR_ENTRY(152, "Sem analysis: ������� �� 0"),*/
		ERROR_ENTRY_NODEF10(160),ERROR_ENTRY_NODEF10(170),ERROR_ENTRY_NODEF10(180),
		ERROR_ENTRY_NODEF10(190),
		ERROR_ENTRY(200, ""),
		ERROR_ENTRY(201, ""),
		ERROR_ENTRY(202, ""),
		ERROR_ENTRY(203, ""),
		ERROR_ENTRY(204, ""),
		ERROR_ENTRY(205, ""),
		ERROR_ENTRY(206, ""),
		ERROR_ENTRY(207, ""),
		ERROR_ENTRY(208, ""),
		ERROR_ENTRY_NODEF100(300),ERROR_ENTRY_NODEF100(400),ERROR_ENTRY_NODEF100(500),ERROR_ENTRY_NODEF100(600),ERROR_ENTRY_NODEF100(700),
		ERROR_ENTRY_NODEF100(800),ERROR_ENTRY_NODEF100(900)
	};

	ERROR geterror(int id)
	{
		if (id > ERROR_MAX_ENTRY || id < 0)
			return errors[0];
		else
			return errors[id];
	}
	ERROR geterrorin(int id, int line, int col)
	{
		if (id > ERROR_MAX_ENTRY || id < 0)
			return errors[0];
		else
		{
			ERROR error = errors[id];
			error.inext.line = line;
			error.inext.col = col;
			return error;
		}
	}
};