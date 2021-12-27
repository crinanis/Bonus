#include "stdafx.h"

using namespace In;
using namespace LT;
using namespace IT;

static bool flag_for_declaration = false;

namespace LA 
{
	void LexAnalysis(const IN& source, LexTable& lexTable, IdTable& idTable)
	{
		int NumOfString = 0;
		int ColInString = 0;
		int table[] = IN_CODE_TABLE;
		int tmpSize = 0;
		char tmp[100];
		bool FlagForStringLiteral = false;

		for (int i = 0; i < source.file_size; i++)
		{
			if (table[(unsigned char)(source.text[i])] != IN::A)
			{
				tmp[tmpSize] = source.text[i];
				tmpSize++;
				ColInString++;
				continue;
			}
			else
			{
				if (tmpSize != 0)
				{
					tmp[tmpSize] = '\0';
					if (TokenAnalysis(tmp, NumOfString, lexTable, idTable, ColInString - 1))
					{
						tmp[0] = '\0';
						tmpSize = 0;
						i--;
						continue;
					}
					else
  						throw ERROR_THROW_IN(120, NumOfString, ColInString - 1);
				}
				else
				{
					if (source.text[i] == '\'')
					{
						tmp[tmpSize++] = source.text[i++];
						for (int SizeOfStringLiteral = 0; source.text[i] != '\''; SizeOfStringLiteral++, i++, tmpSize++)
						{
							if (SizeOfStringLiteral <= IDENT_STR_MAXSIZE)
							{
								tmp[tmpSize] = source.text[i];
								ColInString++;
							}
							else
								throw ERROR_THROW_IN(121, NumOfString, ColInString - 1);
						}
						tmp[tmpSize++] = source.text[i];
						tmp[tmpSize] = '\0';
						if (TokenAnalysis(tmp, NumOfString, lexTable, idTable, ColInString - 1))
						{
							tmp[0] = '\0';
							tmpSize = 0;
							continue;
						}
						else
							throw ERROR_THROW_IN(120, NumOfString, ColInString - 1);
					}
					else if (source.text[i] == '{' && lexTable.table[lexTable.current_size - 1].lexema == LEX_DATAELEMENTS)
					{
						flag_for_declaration = true;
						tmp[tmpSize] = source.text[i];
						tmpSize++;
						ColInString++;
						continue;
					}
					else if (source.text[i] == '}' && flag_for_declaration)
					{
						flag_for_declaration = false;
						tmp[tmpSize] = source.text[i];
						tmpSize++;
						ColInString++;
						continue;
					}
					else if (source.text[i] == '|')
					{
						NumOfString++;
						ColInString = 0;
						continue;
					}
					else if (source.text[i] == ' ')
					{
						ColInString++;
						continue;
					}
					else
					{
						tmp[tmpSize++] = source.text[i];
						tmp[tmpSize] = '\0';
						if (TokenAnalysis(tmp, NumOfString, lexTable, idTable, ColInString - 1))
						{
							tmp[0] = '\0';
							ColInString++;
							tmpSize = 0;
							continue;
						}
						else
							throw ERROR_THROW_IN(120, NumOfString, ColInString - 1);
					}
				}
			}
		}
	}

	bool TokenAnalysis(char* token, int strNumber, LexTable& lexTable, IdTable& idTable, int colinstring)
	{
		static TypeOfVariable tov;

		switch (token[0])
		{
		case LEX_SEMICOLON:
		{
			LT::Add(lexTable, { LEX_SEMICOLON, strNumber, (int)LT_TI_NULLXDX });
			return true;
			break;
		}

		case LEX_COMMA:
		{
			LT::Add(lexTable, { LEX_COMMA, strNumber, (int)LT_TI_NULLXDX });
			return true;
			break;
		}

		case LEX_LEFTBRACE:
		{
			LT::Add(lexTable, { LEX_LEFTBRACE, strNumber, (int)LT_TI_NULLXDX });
			return true;
			break;
		}

		case LEX_RIGHTBRACE:
		{
			LT::Add(lexTable, { LEX_RIGHTBRACE, strNumber, (int)LT_TI_NULLXDX });
			return true;
			break;
		}

		case LEX_LEFTHESIS:
		{
			LT::Add(lexTable, { LEX_LEFTHESIS, strNumber, (int)LT_TI_NULLXDX });
			return true;
			break;
		}

		case LEX_EQUAL_SIGN:
		{
			LT::Add(lexTable, { LEX_EQUAL_SIGN, strNumber, (int)LT_TI_NULLXDX });
			return true;
			break;
		}

		case LEX_REFERENSE:
		{
			LT::Add(lexTable, { LEX_REFERENSE, strNumber, (int)LT_TI_NULLXDX });
			return true;
			break;
		}

		case LEX_RIGHTHESIS:
		{
			LT::Add(lexTable, { LEX_RIGHTHESIS, strNumber, (int)LT_TI_NULLXDX });
			return true;
			break;
		}

		case LEX_PLUS:
		{
			LT::Add(lexTable, { LEX_PLUS, strNumber, (int)LT_TI_NULLXDX });
			return true;
			break;
		}

		case LEX_MINUS:
		{
			LT::Add(lexTable, { LEX_MINUS, strNumber, (int)LT_TI_NULLXDX });
			return true;
			break;
		}

		case LEX_STAR:
		{
			LT::Add(lexTable, { LEX_STAR, strNumber, (int)LT_TI_NULLXDX });
			return true;
			break;
		}

		case LEX_DIRSLASH:
		{
			LT::Add(lexTable, { LEX_DIRSLASH, strNumber, (int)LT_TI_NULLXDX });
			return true;
			break;
		}

		case LEX_MORE_OR_EQUAL:
		{
			LT::Add(lexTable, { LEX_MORE_OR_EQUAL, strNumber, (int)LT_TI_NULLXDX });
			return true;
			break;
		}

		case (char)92: /* \ */
		{
			LT::Add(lexTable, { LEX_LESS_OR_EQUAL, strNumber, (int)LT_TI_NULLXDX });
			return true;
			break;
		}

		case LEX_MORE:
		{
			LT::Add(lexTable, { LEX_MORE, strNumber, (int)LT_TI_NULLXDX });
			return true;
			break;
		}

		case LEX_LESS:
		{
			LT::Add(lexTable, { LEX_LESS, strNumber, (int)LT_TI_NULLXDX });
			return true;
			break;
		}

		case LEX_LEFT_SQ_BRACE:
		{
			LT::Add(lexTable, { LEX_LEFT_SQ_BRACE, strNumber, (int)LT_TI_NULLXDX });
			return true;
			break;
		}

		case LEX_RIGHT_SQ_BRACE:
		{
			LT::Add(lexTable, { LEX_RIGHT_SQ_BRACE, strNumber, (int)LT_TI_NULLXDX });
			return true;
			break;
		}

		case 'i':
		{
			if( token[1] == 'f')
			{
				FST::FST* auto_value = new FST::FST(IF(token));
				if (FST::execute(*auto_value))
				{
					LT::Add(lexTable, { LEX_CONDITION, strNumber, (int)LT_TI_NULLXDX });
					delete auto_value;
					auto_value = NULL;
					return true;
				}
				else
				{
					delete auto_value;
					auto_value = NULL;
					return IdentificatorAnalysis(token, strNumber, lexTable, idTable, tov, colinstring);
				}
			}
			else
			{
				FST::FST* auto_value = new FST::FST(INT(token));
				if (FST::execute(*auto_value))
				{
					LT::Add(lexTable, { LEX_INT, strNumber, (int)LT_TI_NULLXDX });
					delete auto_value;
					auto_value = NULL;
					tov.LT_position = lexTable.current_size - 1;
					tov.type_of_variable = TypeOfVariable::INT;
					return true;
				}
				else
				{
					delete auto_value;
					auto_value = NULL;
					return IdentificatorAnalysis(token, strNumber, lexTable, idTable, tov, colinstring);
				}
			}
			break;
		}

		case 'M':
		{
			FST::FST* auto_value = new FST::FST(MAJOR_FUNCTION(token));
			if (FST::execute(*auto_value))
			{
				LT::Add(lexTable, { LEX_MAJOR, strNumber, (int)LT_TI_NULLXDX });
				delete auto_value;
				auto_value = NULL;
				return true;
			}
			else
			{
				delete auto_value;
				auto_value = NULL;
				return IdentificatorAnalysis(token, strNumber, lexTable, idTable, tov, colinstring);
			}
			break;
		}

		case 'e':
		{
			FST::FST* auto_value = new FST::FST(EQUALS(token));
			if (FST::execute(*auto_value))
			{
				LT::Add(lexTable, { LEX_EQUALS, strNumber, (int)LT_TI_NULLXDX });
				delete auto_value;
				auto_value = NULL;
				return true;
			}
			else
			{
				delete auto_value;
				auto_value = NULL;
				return IdentificatorAnalysis(token, strNumber, lexTable, idTable, tov, colinstring);
			}
			break;
		}

		case 'w':
		{
			FST::FST* auto_value = new FST::FST(WHILE(token));
			if (FST::execute(*auto_value))
			{
				LT::Add(lexTable, { LEX_WHILE, strNumber, (int)LT_TI_NULLXDX });
				delete auto_value;
				auto_value = NULL;
				return true;
			}
			else
			{
				delete auto_value;
				auto_value = NULL;
				return IdentificatorAnalysis(token, strNumber, lexTable, idTable, tov, colinstring);
			}
			break;
		}

		case 't':
		{
			FST::FST* auto_value = new FST::FST(TRUE(token));
			if (FST::execute(*auto_value))
			{
				IT::Entry entry;
				entry.iddatatype = BOO;
				entry.idtype = L;
				strcpy_s(entry.id, "");
				strcpy_s(entry.parrent_block_name, "");

				Add(idTable, entry);
				idTable.table[idTable.current_size - 1].value.vlogic = true;
				Add(lexTable, { LEX_LITERAL, strNumber, idTable.current_size - 1 });

				delete auto_value;
				auto_value = NULL;
				return true;
			}
			else
			{
				throw ERROR_THROW_IN(124, strNumber, colinstring);
				delete auto_value;
				auto_value = NULL;
				return IdentificatorAnalysis(token, strNumber, lexTable, idTable, tov, colinstring);
			}
			break;
		}

		case 'f':
		{
			FST::FST* auto_value = new FST::FST(FALSE(token));
			if (FST::execute(*auto_value))
			{

				IT::Entry entry;
				entry.iddatatype = BOO;
				entry.idtype = L;
				strcpy_s(entry.id, "");
				strcpy_s(entry.parrent_block_name, "");

				Add(idTable, entry);
				idTable.table[idTable.current_size - 1].value.vlogic = false;
				Add(lexTable, { LEX_LITERAL, strNumber, idTable.current_size - 1 });

				delete auto_value;
				auto_value = NULL;
				return true;
			}
			auto_value = new FST::FST(FUNCTION(token));
			if (FST::execute(*auto_value))
			{
				LT::Add(lexTable, { LEX_FUNCTION, strNumber, (int)LT_TI_NULLXDX });
				delete auto_value;
				auto_value = NULL;
				return true;
			}
			else
			{
				delete auto_value;
				auto_value = NULL;
				return IdentificatorAnalysis(token, strNumber, lexTable, idTable, tov, colinstring);
			}
			break;
		}

		case 'd':
		{
			FST::FST* auto_value = new FST::FST(DATAELEMENTS(token));
			if (FST::execute(*auto_value))
			{
				LT::Add(lexTable, { LEX_DATAELEMENTS, strNumber, (int)LT_TI_NULLXDX });
				delete auto_value;
				auto_value = NULL;
				return true;
			}
			else
			{
				delete auto_value;
				auto_value = NULL;
				return IdentificatorAnalysis(token, strNumber, lexTable, idTable, tov, colinstring);
			}
			break;
		}

		case 'r':
		{
			FST::FST* auto_value = new FST::FST(RETURN(token));
			if (FST::execute(*auto_value))
			{
				LT::Add(lexTable, { LEX_RETURN, strNumber, (int)LT_TI_NULLXDX });
				delete auto_value;
				auto_value = NULL;
				return true;
			}
			else
			{
				delete auto_value;
				auto_value = NULL;
				return IdentificatorAnalysis(token, strNumber, lexTable, idTable, tov, colinstring);
			}
			break;
		}

		case 's':
		{
			FST::FST* auto_value = new FST::FST(STRING(token));
			if (FST::execute(*auto_value))
			{
				LT::Add(lexTable, { LEX_STRING, strNumber, (int)LT_TI_NULLXDX });
				delete auto_value;
				auto_value = NULL;
				tov.LT_position = lexTable.current_size - 1;
				tov.type_of_variable = TypeOfVariable::STRING;
				return true;
			}
			else
			{
				delete auto_value;
				auto_value = NULL;
				return IdentificatorAnalysis(token, strNumber, lexTable, idTable, tov, colinstring);
			}
			break;
		}

		case 'b':
		{
			FST::FST* auto_value = new FST::FST(BOOL(token));
			if (FST::execute(*auto_value))
			{
				LT::Add(lexTable, { LEX_BOOL, strNumber, (int)LT_TI_NULLXDX });
				delete auto_value;
				auto_value = NULL;
				tov.LT_position = lexTable.current_size - 1;
				tov.type_of_variable = TypeOfVariable::BOOL;
				return true;
			}
			else
			{
				delete auto_value;
				auto_value = NULL;
				return IdentificatorAnalysis(token, strNumber, lexTable, idTable, tov, colinstring);
			}
			break;
		}

		case 'p':
		{
			FST::FST* auto_value = new FST::FST(PRINT(token));
			if (FST::execute(*auto_value))
			{
				LT::Add(lexTable, { LEX_PRINT, strNumber, (int)LT_TI_NULLXDX });
				delete auto_value;
				auto_value = NULL;
				return true;
			}
			else
			{
				delete auto_value;
				auto_value = NULL;
				return IdentificatorAnalysis(token, strNumber, lexTable, idTable, tov, colinstring);
			}
			break;
		}

		case '\'':
		{
			FST::FST* auto_value = new FST::FST(STRING_LITERAL(token));
			if (FST::execute(*auto_value))
			{
				IT::Entry entry;
				entry.iddatatype = STR;
				entry.idtype = L;
				strcpy_s(entry.id, "");
				strcpy_s(entry.parrent_block_name, "");

				Add(idTable, entry);
				idTable.table[idTable.current_size - 1].value.vstr->len = 0;
				int i = 0, j = 0;
				for (; token[i] != '\0'; i++)
				{
					if (token[i] != '\'')
					{
						idTable.table[idTable.current_size - 1].value.vstr->str[j] = token[i];
						idTable.table[idTable.current_size - 1].value.vstr->len++;
						j++;
					}
				}
				idTable.table[idTable.current_size - 1].value.vstr->str[j] = '\0';
				Add(lexTable, { LEX_LITERAL, strNumber, idTable.current_size - 1 });

				delete auto_value;
				auto_value = NULL;
				return true;
			}
			else
			{
				delete auto_value;
				auto_value = NULL;
				return IdentificatorAnalysis(token, strNumber, lexTable, idTable, tov, colinstring);
			}
			break;
		}

		case '0':
		{
			FST::FST* auto_value = new FST::FST(OCT_LITERAL(token));
			if (FST::execute(*auto_value))
			{
				IT::Entry entry;
				entry.iddatatype = INT;
				entry.idtype = L;
				strcpy_s(entry.id, "");
				strcpy_s(entry.parrent_block_name, "");

				Add(idTable, entry);
				idTable.table[idTable.current_size - 1].value.vint.value = (int)strtol(token, &token, 8);
				Add(lexTable, { LEX_LITERAL, strNumber, idTable.current_size - 1 });

				delete auto_value;
				auto_value = NULL;
				return true;
			}
			else
			{
				delete auto_value;
				auto_value = NULL;
				return false;
			}
		}

		default:
		{
			FST::FST* auto_value = new FST::FST(INTEGER_LITERAL(token));
			if (FST::execute(*auto_value))
			{
				IT::Entry entry;
				entry.iddatatype = INT;
				entry.idtype = L;
				strcpy_s(entry.id, "");
				strcpy_s(entry.parrent_block_name, "");

				Add(idTable, entry);
				if (atoi(token) >= INT_MAX)
					throw ERROR_THROW_IN(144, strNumber, colinstring);
				idTable.table[idTable.current_size - 1].value.vint.value = atoi(token);
				Add(lexTable, { LEX_LITERAL, strNumber, idTable.current_size - 1 });

				delete auto_value;
				auto_value = NULL;
				return true;
			}
			else
			{
				delete auto_value;
				auto_value = NULL;
				return IdentificatorAnalysis(token, strNumber, lexTable, idTable, tov, colinstring);
			}
		}
		}
	}

	bool IdentificatorAnalysis(char* token, const int strNumber, LT::LexTable& lexTable, IT::IdTable& idTable, TypeOfVariable& type, int colinstring)
	{

		FST::FST* identificator = new FST::FST(IDENTIFICATOR(token));
		if (FST::execute(*identificator))
		{
			bool is_already_checked = false;
			char ready_id[5] = {};
			int i = 0;

			if (flag_for_declaration)
			{
				

#pragma region IS_ARRAY

				if (!is_already_checked && (lexTable.table[lexTable.current_size - 1].lexema == LEX_RIGHT_SQ_BRACE && lexTable.table[lexTable.current_size - 2].lexema == LEX_LITERAL && lexTable.table[lexTable.current_size - 3].lexema == LEX_LEFT_SQ_BRACE && type.LT_position == lexTable.current_size - 4))
				{
					if (IsId(idTable, token) == IDENT_NULLIDX || idTable.table[IsId(idTable, token)].idtype != V || strcmp(idTable.table[IsId(idTable, token)].parrent_block_name, idTable.table[lexTable.table[lexTable.current_size].idxTI].id) != 0)
					{
						IT::Entry entry;
						strcpy_s(entry.parrent_block_name, "major");
						strcpy_s(entry.id, token);
						entry.iddatatype = INT;
						entry.idtype = A;

						if (type.type_of_variable == TypeOfVariable::INT)
						{
							entry.value.vint.array_size = idTable.table[lexTable.table[lexTable.current_size - 2].idxTI].value.vint.value;
							IT::Add(idTable, entry);
						}

						if (type.type_of_variable == TypeOfVariable::STRING)
						{
							throw ERROR_THROW_IN(141, strNumber, colinstring);
						}

						if (type.type_of_variable == TypeOfVariable::BOOL)
						{
							throw ERROR_THROW_IN(142, strNumber, colinstring);
						}

						type.LT_position = -1;
						type.type_of_variable = TypeOfVariable::UNDEF;

						LT::Add(lexTable, { LEX_ID, strNumber, idTable.current_size - 1 });
						is_already_checked = true;
					}
					else
						throw ERROR_THROW_IN(126, strNumber, colinstring);
				}

#pragma endregion

#pragma IS_ARRAY_WITH_REFERENSE

				if (!is_already_checked && (lexTable.table[lexTable.current_size - 1].lexema == LEX_RIGHT_SQ_BRACE && lexTable.table[lexTable.current_size - 2].lexema == LEX_LITERAL && lexTable.table[lexTable.current_size - 3].lexema == LEX_LEFT_SQ_BRACE && lexTable.table[lexTable.current_size - 4].lexema == LEX_REFERENSE && lexTable.table[lexTable.current_size - 5].lexema == LEX_ID && type.LT_position == lexTable.current_size - 7))
				{
					if (IsId(idTable, token) == IDENT_NULLIDX || idTable.table[IsId(idTable, token)].idtype != V || strcmp(idTable.table[IsId(idTable, token)].parrent_block_name, idTable.table[lexTable.table[lexTable.current_size].idxTI].id) != 0)
					{
						IT::Entry entry;
						strcpy_s(entry.parrent_block_name, idTable.table[lexTable.table[lexTable.current_size - 2].idxTI].id);
						strcpy_s(entry.id, token);
						entry.iddatatype = INT;
						entry.idtype = A;

						if (type.type_of_variable == TypeOfVariable::INT)
						{
							entry.value.vint.array_size = idTable.table[lexTable.table[lexTable.current_size - 2].idxTI].value.vint.value;
							IT::Add(idTable, entry);
						}

						if (type.type_of_variable == TypeOfVariable::STRING)
						{
							throw ERROR_THROW_IN(141, strNumber, colinstring);
						}

						if (type.type_of_variable == TypeOfVariable::BOOL)
						{
							throw ERROR_THROW_IN(142, strNumber, colinstring);
						}

						type.LT_position = -1;
						type.type_of_variable = TypeOfVariable::UNDEF;

						LT::Add(lexTable, { LEX_ID, strNumber, idTable.current_size - 1 });
						is_already_checked = true;
					}
					else
						throw ERROR_THROW_IN(126, strNumber, colinstring);
				}

#pragma endregion

#pragma region IS_DECLARE

				if (!is_already_checked && (lexTable.table[lexTable.current_size - 1].lexema == 't' && (lexTable.table[lexTable.current_size - 2].lexema == ';' || lexTable.table[lexTable.current_size - 2].lexema == '{') && type.LT_position == lexTable.current_size - 1))
				{
					if (IsId(idTable, token) == IDENT_NULLIDX || idTable.table[IsId(idTable, token)].idtype != V && strcmp(idTable.table[IsId(idTable, token)].parrent_block_name, idTable.table[lexTable.table[lexTable.current_size].idxTI].id) != 0)
					{
						IT::Entry entry;
						strcpy_s(entry.parrent_block_name, "major");
						strcpy_s(entry.id, token);
						entry.iddatatype = INT;
						entry.idtype = V;

						if (type.type_of_variable == TypeOfVariable::INT)
						{
							entry.value.vint.value = 0;
							IT::Add(idTable, entry);
						}

						if (type.type_of_variable == TypeOfVariable::STRING)
						{
							entry.iddatatype = STR;
							entry.value.vstr->len = 0;
							strcpy_s(entry.value.vstr->str, "");
							IT::Add(idTable, entry);
						}

						if (type.type_of_variable == TypeOfVariable::BOOL)
						{
							entry.iddatatype = BOO;
							entry.value.vlogic = false;
							IT::Add(idTable, entry);
						}

						type.LT_position = -1;
						type.type_of_variable = TypeOfVariable::UNDEF;

						LT::Add(lexTable, { LEX_ID, strNumber, idTable.current_size - 1 });
						is_already_checked = true;
					}
					else
						throw ERROR_THROW_IN(126, strNumber, colinstring);
				}

#pragma endregion

#pragma region PARM_OF_PROTO_FUNCTION

				if (!is_already_checked && (GetEntry(lexTable, lexTable.current_size - 1).lexema == 't' && type.LT_position == lexTable.current_size - 1))
					for (int i = lexTable.current_size - 1; i > 0; i--)
					{

						if (lexTable.table[i].lexema == LEX_ID && idTable.table[lexTable.table[i].idxTI].idtype == IT::IDTYPE::PF)
						{
							if (GetEntry(lexTable, i - 1).lexema == LEX_FUNCTION && GetEntry(lexTable, i - 2).lexema == 't')
							{
								IT::Entry entry;
								strcpy_s(entry.parrent_block_name, idTable.table[lexTable.table[i].idxTI].id);
								strcpy_s(entry.id, token);
								entry.iddatatype = INT;
								entry.idtype = P;
								idTable.table[lexTable.table[i].idxTI].value.vint.parm_count++;

								if (type.type_of_variable == TypeOfVariable::INT)
									IT::Add(idTable, entry);

								if (type.type_of_variable == TypeOfVariable::STRING)
								{
									entry.iddatatype = STR;
									IT::Add(idTable, entry);
								}

								if (type.type_of_variable == TypeOfVariable::BOOL)
								{
									entry.iddatatype = BOO;
									IT::Add(idTable, entry);
								}

								type.LT_position = -1;
								type.type_of_variable = TypeOfVariable::UNDEF;

								LT::Add(lexTable, { LEX_ID, strNumber, idTable.current_size - 1 });
								is_already_checked = true;
								break;
							}
						}
					}
#pragma endregion

#pragma region IS_DECLARE_WITH_REF

				if (!is_already_checked && (lexTable.table[lexTable.current_size - 1].lexema == LEX_REFERENSE && lexTable.table[lexTable.current_size - 2].lexema == LEX_ID && lexTable.table[lexTable.current_size - 3].lexema == LEX_REFERENSE && type.LT_position == lexTable.current_size - 4))
				{
					if (IsId(idTable, token) == IDENT_NULLIDX || idTable.table[IsId(idTable, token)].idtype != V || idTable.table[IsId(idTable, token)].parrent_block_name != idTable.table[lexTable.table[i].idxTI].id)
					{
						IT::Entry entry;
						strcpy_s(entry.parrent_block_name, idTable.table[lexTable.table[lexTable.current_size - 2].idxTI].id);
						strcpy_s(entry.id, token);
						entry.iddatatype = INT;
						entry.idtype = V;

						if (type.type_of_variable == TypeOfVariable::INT)
							IT::Add(idTable, entry);

						if (type.type_of_variable == TypeOfVariable::STRING)
						{
							entry.iddatatype = STR;
							IT::Add(idTable, entry);
						}

						if (type.type_of_variable == TypeOfVariable::BOOL)
						{
							entry.iddatatype = BOO;
							IT::Add(idTable, entry);
						}

						type.LT_position = -1;
						type.type_of_variable = TypeOfVariable::UNDEF;

						LT::Add(lexTable, { LEX_ID, strNumber, idTable.current_size - 1 });
						is_already_checked = true;
					}
					else
						throw ERROR_THROW_IN(126, strNumber, colinstring);
				}

#pragma endregion

#pragma region IS_PROTO_FUNCTION

				if (strcmp(token, "major") == 0 || (!is_already_checked && ((GetEntry(lexTable, lexTable.current_size - 1).lexema == LEX_FUNCTION && GetEntry(lexTable, lexTable.current_size - 2).lexema == 't') && type.LT_position == lexTable.current_size - 2)))
				{
					IT::Entry entry;
					strcpy_s(entry.parrent_block_name, "");
					strcpy_s(entry.id, token);
					entry.iddatatype = INT;
					entry.idtype = PF;
					entry.value.vint.parm_count = 0;

					if (IsId(idTable, token) == -1 || idTable.table[IsId(idTable, token)].idtype != PF)
					{
						if (strcmp(token, "major") == 0)
						{
							IT::Add(idTable, entry);
							LT::Add(lexTable, { LEX_MAJOR, strNumber, idTable.current_size - 1 });
						}
						else
						{
							if (type.type_of_variable == TypeOfVariable::INT)
								IT::Add(idTable, entry);

							if (type.type_of_variable == TypeOfVariable::STRING)
							{
								entry.iddatatype = STR;
								IT::Add(idTable, entry);
							}

							if (type.type_of_variable == TypeOfVariable::BOOL)
							{
								entry.iddatatype = BOO;
								IT::Add(idTable, entry);
							}

							LT::Add(lexTable, { LEX_ID, strNumber, idTable.current_size - 1 });
						}

						type.LT_position = -1;
						type.type_of_variable = TypeOfVariable::UNDEF;


						is_already_checked = true;
					}
					else
						throw ERROR_THROW_IN(123, strNumber, colinstring);
				}

#pragma endregion



#pragma region ID_WITHOUT_DECLARE

				if (!is_already_checked)
				{

					int tempIndex = IsId(idTable, token);
					if (tempIndex != -1)
					{
						LT::Add(lexTable, { LEX_ID, strNumber, tempIndex });
					}
					else
					{
						throw ERROR_THROW_IN(129, strNumber, colinstring);
					}
					is_already_checked = true;

				}

#pragma endregion
			}
			else
			{

#pragma region IS_FUNCTION

				if ((strcmp(token, "major") == 0 || strcmp(token, "printcurrentdate") == 0 || strcmp(token, "isleap") == 0) || (!is_already_checked && ((GetEntry(lexTable, lexTable.current_size - 1).lexema == LEX_FUNCTION && GetEntry(lexTable, lexTable.current_size - 2).lexema == 't') && type.LT_position == lexTable.current_size - 2)))
				{
					IT::Entry entry;
					strcpy_s(entry.parrent_block_name, "");
					strcpy_s(entry.id, token);
					entry.iddatatype = INT;
					entry.idtype = F;
					entry.value.vint.parm_count = 0;

					if (IsId(idTable, token) == -1 || idTable.table[IsId(idTable, token)].idtype != F)
					{
						if (strcmp(token, "major") == 0)
						{
							IT::Add(idTable, entry);
							LT::Add(lexTable, { LEX_MAJOR, strNumber, idTable.current_size - 1 });
						}
						else if (strcmp(token, "printcurrentdate") == 0)
						{
							entry.idtype = PF;
							entry.value.vint.parm_count = 0;
							IT::Add(idTable, entry);
							LT::Add(lexTable, { LEX_ID, strNumber, idTable.current_size - 1 });
						}
						else if (strcmp(token, "isleap") == 0)
						{
							entry.idtype = PF;
							entry.value.vint.parm_count = 1;
							IT::Add(idTable, entry);
							LT::Add(lexTable, { LEX_ID, strNumber, idTable.current_size - 1 });
						}
						else 
						{
							if (type.type_of_variable == TypeOfVariable::INT)
								IT::Add(idTable, entry);

							if (type.type_of_variable == TypeOfVariable::STRING)
							{
								entry.iddatatype = STR;
								IT::Add(idTable, entry);
							}

							if (type.type_of_variable == TypeOfVariable::BOOL)
							{
								entry.iddatatype = BOO;
								IT::Add(idTable, entry);
							}

							LT::Add(lexTable, { LEX_ID, strNumber, idTable.current_size - 1 });
						}

						type.LT_position = -1;
						type.type_of_variable = TypeOfVariable::UNDEF;


						is_already_checked = true;
					}
					else
						throw ERROR_THROW_IN(123, strNumber, colinstring);
				}

#pragma endregion

#pragma region PARM_OF_FUNCTION

				if (!is_already_checked && (GetEntry(lexTable, lexTable.current_size - 1).lexema == 't' && type.LT_position == lexTable.current_size - 1))
				{
					if (lexTable.table[lexTable.current_size - 2].lexema == ',' || lexTable.table[lexTable.current_size - 2].lexema == '(')
					{
						for (int i = lexTable.current_size - 1; i > 0; i--)
						{

							if (lexTable.table[i].lexema == LEX_ID && idTable.table[lexTable.table[i].idxTI].idtype == IT::IDTYPE::F)
							{
								if (GetEntry(lexTable, i - 1).lexema == LEX_FUNCTION && GetEntry(lexTable, i - 2).lexema == 't')
								{
									IT::Entry entry;
									strcpy_s(entry.parrent_block_name, idTable.table[lexTable.table[i].idxTI].id);
									strcpy_s(entry.id, token);
									entry.iddatatype = INT;
									entry.idtype = P;
									idTable.table[lexTable.table[i].idxTI].value.vint.parm_count++;

									if (type.type_of_variable == TypeOfVariable::INT)
										IT::Add(idTable, entry);

									if (type.type_of_variable == TypeOfVariable::STRING)
									{
										entry.iddatatype = STR;
										IT::Add(idTable, entry);
									}

									if (type.type_of_variable == TypeOfVariable::BOOL)
									{
										entry.iddatatype = BOO;
										IT::Add(idTable, entry);
									}

									type.LT_position = -1;
									type.type_of_variable = TypeOfVariable::UNDEF;

									LT::Add(lexTable, { LEX_ID, strNumber, idTable.current_size - 1 });
									is_already_checked = true;
									break;
								}
							}
						}
					}
				}
			}
#pragma endregion

#pragma region ID_WITHOUT_DECLARE

			if (!is_already_checked)
			{
				if (lexTable.table[lexTable.current_size - 1].lexema != LEX_INT)
				{
					bool isLeftBraceWas = false;
					for (int i = lexTable.current_size - 1; i > 0; i--)
					{
						if (GetEntry(lexTable, i).lexema == LEX_LEFTBRACE)
						{
							isLeftBraceWas = true;
						}

						if (isLeftBraceWas && ((lexTable.table[i].lexema == LEX_ID && idTable.table[lexTable.table[i].idxTI].idtype == IT::IDTYPE::F) || lexTable.table[i].lexema == LEX_MAJOR))
						{
							int tempIndex = IsId(idTable, token);
							if (lexTable.table[i].lexema == LEX_MAJOR)
							{
								if (tempIndex != -1 && idTable.table[tempIndex].idtype == IT::IDTYPE::PF)
								{
									LT::Add(lexTable, { LEX_ID, strNumber, tempIndex });
									break;
								}
								if (tempIndex != -1 && !strcmp(idTable.table[tempIndex].parrent_block_name, "major"))
								{
									LT::Add(lexTable, { LEX_ID, strNumber, tempIndex });
									break;
								}
								else
								{
									throw ERROR_THROW_IN(129, strNumber, colinstring);
								}
							}
							else
							{
								if (tempIndex != -1 && !strcmp(idTable.table[tempIndex].parrent_block_name, idTable.table[lexTable.table[i].idxTI].id))
								{
									LT::Add(lexTable, { LEX_ID, strNumber, tempIndex });
									break;
								}
								else
								{
									throw ERROR_THROW_IN(129, strNumber, colinstring);
								}
							}

						}
					}
				}
				else
					return false;
			}

#pragma endregion

			return true;

#pragma endregion

		}
		else
		{
			delete identificator;
			identificator = NULL;
			return false;
		}
	}
}