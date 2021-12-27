#define _CRT_SECURE_NO_WARNINGS

#include "stdafx.h"

void code_block_generation(std::ofstream* file, int& i, LT::LexTable& LexTable, IT::IdTable& IdTable)
{
	while (LexTable.table[++i].lexema != LEX_RIGHTBRACE)
	{
		if (LexTable.table[i].lexema == LEX_EQUALS)
		{
			int indOflex = i-1;
			bool is_already_checked = false;
			
			while (LexTable.table[i].lexema != LEX_SEMICOLON)
			{
				if (LexTable.table[i].lexema == LEX_ID && IdTable.table[LexTable.table[i].idxTI].idtype == IT::IDTYPE::A)
				{
					if(IdTable.table[LexTable.table[i + 2].idxTI].idtype == IT::IDTYPE::L)
						*file << "push " << IdTable.table[LexTable.table[i].idxTI].id << "[4*" << IdTable.table[LexTable.table[i + 2].idxTI].value.vint.value << "]\n";
					else
					{
						*file << "mov esi, " << IdTable.table[LexTable.table[i + 2].idxTI].id << std::endl;
						*file << "push " << IdTable.table[LexTable.table[i].idxTI].id << "[4*esi]\n";
					}
					i += 3;
				}
				else if ((LexTable.table[i].lexema == LEX_ID || LexTable.table[i].lexema == LEX_LITERAL) && IdTable.table[LexTable.table[i].idxTI].iddatatype == IT::IDDATATYPE::STR && LexTable.table[i + 1].lexema == LEX_SEMICOLON)
				{
					if (LexTable.table[i].lexema == LEX_ID && IdTable.table[LexTable.table[i].idxTI].idtype == IT::IDTYPE::P)
					{
						*file << "mov edi, " << IdTable.table[LexTable.table[i].idxTI].id << std::endl;
						*file << "push offset edi\n";
					}
					else if (LexTable.table[i].lexema == LEX_ID)
						*file << "push offset " << IdTable.table[LexTable.table[i].idxTI].id << std::endl;
					else
						*file << "push offset L" << LexTable.table[i].idxTI << std::endl;
					*file << "push offset " << IdTable.table[LexTable.table[indOflex].idxTI].id << std::endl;
					*file << "call cat1\n";
					is_already_checked = true;
				}
				else if (LexTable.table[i].lexema == LEX_ID)
				{
					if (IdTable.table[LexTable.table[i].idxTI].idtype == IT::IDTYPE::PF)
					{
						int function_id = i;
						while (LexTable.table[++i].lexema != '@')
						{
							if (IdTable.table[LexTable.table[i].idxTI].idtype == IT::IDTYPE::L)
							{
								if (IdTable.table[LexTable.table[i].idxTI].iddatatype == IT::IDDATATYPE::STR)
									*file << "push offset L" << LexTable.table[i].idxTI << "\n";
								else
									*file << "push L" << LexTable.table[i].idxTI << "\n";
							}
							else
							{
								if (IdTable.table[LexTable.table[i].idxTI].iddatatype == IT::IDDATATYPE::STR)
									*file << "push offset " << IdTable.table[LexTable.table[i].idxTI].id << "\n";
								else
									*file << "push " << IdTable.table[LexTable.table[i].idxTI].id << "\n";
							}
						}

						if(strcmp(IdTable.table[LexTable.table[function_id].idxTI].id, "isleap") != 0  && strcmp(IdTable.table[LexTable.table[function_id].idxTI].id, "printcurrentdate") != 0)
							*file << "call " << "f_" << IdTable.table[LexTable.table[function_id].idxTI].id << "\n";
						else
							*file << "call " << IdTable.table[LexTable.table[function_id].idxTI].id << "\n";

						if(IdTable.table[LexTable.table[function_id].idxTI].iddatatype == IT::IDDATATYPE::STR)
							*file << "push offset eax\n";
						else
							*file << "push eax\n";
						i += 1;
					}
					else
					{
						if (IdTable.table[LexTable.table[i].idxTI].idtype == IT::IDTYPE::P && IdTable.table[LexTable.table[i].idxTI].iddatatype == IT::IDDATATYPE::STR)
						{
							*file << "mov edi, " << IdTable.table[LexTable.table[i].idxTI].id << std::endl;
							*file << "push edi\n";
						}
						else if (IdTable.table[LexTable.table[i].idxTI].iddatatype == IT::IDDATATYPE::STR)
							*file << "push offset " << IdTable.table[LexTable.table[i].idxTI].id << "\n";
						else
							*file << "push " << IdTable.table[LexTable.table[i].idxTI].id << "\n";
					}
				}
				else if (LexTable.table[i].lexema == LEX_LITERAL)
				{
					if (IdTable.table[LexTable.table[i].idxTI].iddatatype == IT::IDDATATYPE::STR)
						*file << "push offset L" << LexTable.table[i].idxTI << "\n";
					else
						*file << "push L" << LexTable.table[i].idxTI << "\n";
				}

				if (LexTable.table[i].lexema == LEX_PLUS)
				{
					*file << "pop eax\n";
					*file << "pop ebx\n";
					*file << "add eax, ebx\n";
					*file << "push eax\n";
				}
				if (LexTable.table[i].lexema == LEX_CONCAT)
				{
					*file << "push offset tmp1\n";
					*file << "call cat2\n";
					*file << "push offset tmp1\n";
					*file << "push offset " << IdTable.table[LexTable.table[indOflex].idxTI].id << std::endl;
					*file << "call cat1\n";
					is_already_checked = true;
				}
				if (LexTable.table[i].lexema == LEX_MINUS)
				{
					*file << "pop ebx\n";
					*file << "pop eax\n";
					*file << "sub eax, ebx\n";
					*file << "push eax\n";
				}
				if (LexTable.table[i].lexema == LEX_STAR)
				{
					*file << "pop eax\n";
					*file << "pop ebx\n";
					*file << "mul ebx\n";
					*file << "push eax\n";
				}
				if (LexTable.table[i].lexema == LEX_DIRSLASH)
				{
					*file << "pop eax\n";
					*file << "pop ebx\n";
					*file << "div ebx\n";
					*file << "push eax\n";
				}
				i++;
			}
			if (!is_already_checked)
			{
				*file << "pop " << IdTable.table[LexTable.table[indOflex].idxTI].id << "\n";
			}
				
		}

		if (LexTable.table[i].lexema == LEX_RETURN)
		{
			if (LexTable.table[i + 1].lexema == LEX_ID)
			{
				if (IdTable.table[LexTable.table[i + 1].idxTI].iddatatype == IT::IDDATATYPE::STR)
					*file << "mov eax, offset " << IdTable.table[LexTable.table[i + 1].idxTI].id << "\n\tret\n";
				else
					*file << "mov eax, " << IdTable.table[LexTable.table[i + 1].idxTI].id << "\n\tret\n";
			}
			else
			{
				if (IdTable.table[LexTable.table[i + 1].idxTI].iddatatype == IT::IDDATATYPE::STR)
					*file << "mov eax, offset L" << LexTable.table[i + 1].idxTI << "\n\tret\n";
				else
					*file << "mov eax, L" << LexTable.table[i + 1].idxTI << "\n\tret\n";

			}
		}

		if (LexTable.table[i].lexema == LEX_PRINT)
		{
			if (LexTable.table[i + 1].lexema == LEX_ID && IdTable.table[LexTable.table[i + 1].idxTI].idtype == IT::IDTYPE::A)
			{
				if (IdTable.table[LexTable.table[i + 3].idxTI].idtype == IT::IDTYPE::L)
					*file << "push " << IdTable.table[LexTable.table[i + 1].idxTI].id << "[4*" << IdTable.table[LexTable.table[i + 3].idxTI].value.vint.value << "]\n";
				else
				{
					*file << "mov esi, " << IdTable.table[LexTable.table[i + 3].idxTI].id << std::endl;
					*file << "push " << IdTable.table[LexTable.table[i + 1].idxTI].id << "[4*esi]\n";
				}
				*file << "call printint\n";
			}
			else if (LexTable.table[i + 1].lexema == LEX_ID)
			{
				if (IdTable.table[LexTable.table[i + 1].idxTI].iddatatype == IT::IDDATATYPE::STR)
				{
					*file << "push offset " << IdTable.table[LexTable.table[i + 1].idxTI].id << std::endl;
					*file << "call print\n";
				}
				else
				{
					*file << "push " << IdTable.table[LexTable.table[i + 1].idxTI].id << std::endl;
					*file << "call printint\n";
				}
			}
			else
			{
				if (IdTable.table[LexTable.table[i + 1].idxTI].iddatatype == IT::IDDATATYPE::STR)
				{
					*file << "push offset L" << LexTable.table[i + 1].idxTI << std::endl;
					*file << "call print\n";
				}
				else
				{
					*file << "push L" << LexTable.table[i + 1].idxTI << std::endl;
					*file << "call printint\n";
				}
			}
		}

		if (LexTable.table[i].lexema == LEX_CONDITION)
		{
			i += 3;

			if (LexTable.table[i + 1].lexema == LEX_ID && IdTable.table[LexTable.table[i + 1].idxTI].idtype == IT::IDTYPE::A)
			{
				if (IdTable.table[LexTable.table[i + 3].idxTI].idtype == IT::IDTYPE::L)
					*file << "push " << IdTable.table[LexTable.table[i + 1].idxTI].id << "[4*" << IdTable.table[LexTable.table[i + 3].idxTI].value.vint.value << "]\n";
				else
				{
					*file << "mov esi, " << IdTable.table[LexTable.table[i + 3].idxTI].id << std::endl;
				}
				*file << "mov eax, " << IdTable.table[LexTable.table[i + 1].idxTI].id << "[4*esi]\n";
			}
			else if (LexTable.table[i + 1].lexema == LEX_ID)
				*file << "mov eax, " << IdTable.table[LexTable.table[i + 1].idxTI].id << std::endl;
			else
				*file << "mov eax, L" << LexTable.table[i + 1].idxTI << std::endl;

			if (LexTable.table[i - 1].lexema == LEX_ID)
				*file << "cmp eax, " << IdTable.table[LexTable.table[i - 1].idxTI].id << std::endl;
			else
				*file << "cmp eax, L" << LexTable.table[i - 1].idxTI << std::endl;

			if (LexTable.table[i].lexema == LEX_MORE)
			{
				*file << "jae condition_end\n";
			}
			if (LexTable.table[i].lexema == LEX_LESS)
			{
				*file << "jbe condition_end\n";
			}
			if (LexTable.table[i].lexema == LEX_MORE_OR_EQUAL)
			{
				*file << "jb condition_end\n";
			}
			if (LexTable.table[i].lexema == (char)92)
			{
				*file << "ja condition_end\n";
			}
			if (LexTable.table[i].lexema == LEX_EQUAL_SIGN)
			{
				*file << "jne condition_end\n";
			}
			i += 2;
			code_block_generation(file, i, LexTable, IdTable);
			*file << "condition_end: \n";
		}

		if (LexTable.table[i].lexema == LEX_WHILE)
		{
			i += 3;
			*file << "while_start: \n";

			if (LexTable.table[i + 1].lexema == LEX_ID)
				*file << "mov eax, " << IdTable.table[LexTable.table[i + 1].idxTI].id << std::endl;
			else
				*file << "mov eax, L" << LexTable.table[i + 1].idxTI << std::endl;

			if (LexTable.table[i - 1].lexema == LEX_ID)
				*file << "cmp eax, " << IdTable.table[LexTable.table[i - 1].idxTI].id << std::endl;
			else
				*file << "cmp eax, L" << LexTable.table[i - 1].idxTI << std::endl;

			if (LexTable.table[i].lexema == LEX_MORE)
			{
				*file << "jae while_end\n";
			}
			if (LexTable.table[i].lexema == LEX_LESS)
			{
				*file << "jbe while_end\n";
			}
			if (LexTable.table[i].lexema == LEX_MORE_OR_EQUAL)
			{
				*file << "jb while_end\n";
			}
			if (LexTable.table[i].lexema == (char)92)
			{
				*file << "ja while_end\n";
			}
			if (LexTable.table[i].lexema == LEX_EQUAL_SIGN)
			{
				*file << "jne while_end\n";
			}
			i += 2;
			code_block_generation(file, i, LexTable, IdTable);
			*file << "jmp while_start\n";
			*file << "while_end: \n";
		}
	}
}

void generation(LT::LexTable& LexTable, IT::IdTable& IdTable)
{
	std::cout << std::endl;
	std::ofstream* file = new std::ofstream("e:\\LP_KP\\BKA-2021_asm\\BKA-2021_asm.asm");
	if (file->is_open())
	{
		*file << STANDART_BEGIN;
		*file << STANDART_LIB;
		*file << STACK(4096);
		*file << LITERALS_BEGIN;

		for (int i = 0; i < IdTable.current_size; i++)
		{
			if (IdTable.table[i].idtype == IT::IDTYPE::L)
			{
				switch (IdTable.table[i].iddatatype)
				{
				case IT::IDDATATYPE::INT: 
				{
					*file << 'L' << i << "\tsdword\t" << IdTable.table[i].value.vint.value << "\t ; int literal" << '\n';
					break;
				}
				case IT::IDDATATYPE::STR:
				{
					*file << 'L' << i << "\tbyte\t\"";

					for (int j = 0; IdTable.table[i].value.vstr->str[j] != '\0'; j++)
						*file << IdTable.table[i].value.vstr->str[j];

					*file << "\", 0\n";
					break;
				}
				case IT::IDDATATYPE::BOO: 
				{
					*file << 'L' << i << "\tsdword\t";

					if (IdTable.table[i].value.vlogic)
						*file << 1;
					else
						*file << 0;

					*file << "\t ; bool literal" << '\n';
					break; 
				}
				}
			}
		}

		*file << LITERALS_END;

		int concat_count = 0;
		for (int i = 0; i < LexTable.current_size; i++)
			if (LexTable.table[i].lexema == LEX_CONCAT)
				concat_count++;

		*file << VARIABLES_BEGIN;

		for (int i = 0; i < IdTable.current_size; i++)
		{
			if (IdTable.table[i].idtype == IT::IDTYPE::V)
			{
				*file  << IdTable.table[i].id;
				switch (IdTable.table[i].iddatatype)
				{
				case IT::IDDATATYPE::INT:  
				{
					*file << "\tsdword\t" << '0' << "\t ; int variable" << '\n';
					break;
				}

				case IT::IDDATATYPE::STR: 
				{
					*file << "\tbyte\t" << IDENT_STR_MAXSIZE << " dup(0)" << "\t ; string variable" << '\n';
					break;
				}

				case IT::IDDATATYPE::BOO: 
				{
					*file << "\tsdword\t" << '0' << "\t ; bool variable" << '\n'; 
					break;
				}
				}
			}			
		}

		int i = 0;

		while (LexTable.table[i].lexema != LEX_RIGHTBRACE)
		{
			if (LexTable.table[++i].lexema == LEX_ID && IdTable.table[LexTable.table[i].idxTI].idtype == IT::IDTYPE::A)
			{
				int array_id = i;
				*file << IdTable.table[LexTable.table[i].idxTI].id << " sdword ";
				int values_counter = 0;

				while (LexTable.table[++i].lexema != LEX_SEMICOLON)
				{
					if (LexTable.table[i].lexema == LEX_LITERAL)
					{
						values_counter++;
						*file << IdTable.table[LexTable.table[i].idxTI].value.vint.value;
						if (LexTable.table[i + 1].lexema != LEX_SEMICOLON)
							*file << ", ";
						else
							*file << std::endl;
					}
				}
				if (values_counter > IdTable.table[LexTable.table[array_id].idxTI].value.vint.array_size)
					throw ERROR_THROW(145);
			}
		}

		*file << "tmp" << '1' << " byte 255 dup(0)\n";

		*file << VARIABLES_END;

		*file << FUNCTIONS_BEGIN;

		i = 0;

		while (LexTable.table[i].lexema != LEX_RIGHTBRACE)
			i++;

		for (i; i < LexTable.current_size; i++)
		{
			if (LexTable.table[i].lexema == LEX_FUNCTION)
			{
				char function_id[IDENT_MAX_SYMBOLS];
				strcpy(function_id, IdTable.table[LexTable.table[++i].idxTI].id);

				*file <<  "f_" << IdTable.table[LexTable.table[i].idxTI].id << " PROC ";

				while (LexTable.table[++i].lexema != LEX_RIGHTHESIS)
				{
					if (LexTable.table[i].lexema == LEX_ID && IdTable.table[LexTable.table[i].idxTI].idtype == IT::IDTYPE::P)
					{
						if (IdTable.table[LexTable.table[i].idxTI].iddatatype != IT::IDDATATYPE::STR)
						{
							*file << IdTable.table[LexTable.table[i].idxTI].id << " : sdword";
							if (LexTable.table[i + 1].lexema != LEX_RIGHTHESIS)
								*file << ", ";
							else
								*file << std::endl << std::endl;
						}
						else
						{
							*file << IdTable.table[LexTable.table[i].idxTI].id << " : sdword";
							if (LexTable.table[i + 1].lexema != LEX_RIGHTHESIS)
								*file << ", ";
							else
								*file << std::endl << std::endl;
						}
					}
				}

				code_block_generation(file, i, LexTable, IdTable);

				*file << "f_" << function_id << " endp\n\n\n";
			}

			if (LexTable.table[i].lexema == LEX_MAJOR)
			{
				*file << "main PROC" << std::endl << std::endl;
				code_block_generation(file, i, LexTable, IdTable);
				*file << "invoke ExitProcess, 0" << std::endl;
				*file << "main ENDP" << std::endl;
				*file << "end main";
			}
		}

		*file << FUNCTIONS_END;
	}
	else
	{
		throw ERROR_THROW(113);
	}
}