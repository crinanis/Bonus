#pragma once
#include <fstream>

#define IN_MAX_LEN_TEXT 1024*1024
#define IN_CODE_ENDL '\n'
#define IN_SEPARATOR '|'

#define IN_CODE_TABLE {\
/*    0      1         2      3         4      5         6      7         8      9         A      B         C      D         E      F       */ \
	IN::F, IN::F,    IN::F, IN::F,    IN::F, IN::F,    IN::F, IN::T,    IN::T, IN::T,    IN::A, IN::F,    IN::F, IN::F,    IN::F, IN::F, /*0*/ \
	IN::F, IN::F,    IN::F, IN::F,    IN::F, IN::F,    IN::F, IN::F,    IN::F, IN::F,    IN::F, IN::F,    IN::F, IN::F,    IN::T, IN::T, /*1*/ \
	IN::A, IN::T,    IN::F, IN::F,    IN::A, IN::A,    IN::T, IN::A,    IN::A, IN::A,    IN::A, IN::A,    IN::A, IN::A,    IN::A, IN::A, /*2*/ \
	IN::T, IN::T,    IN::T, IN::T,    IN::T, IN::T,    IN::T, IN::T,    IN::T, IN::T,    IN::T, IN::A,    IN::A, IN::A,    IN::A, IN::F, /*3*/ \
	IN::T, IN::T,    IN::T, IN::T,    IN::T, IN::T,    IN::T, IN::T,    IN::T, IN::T,    IN::T, IN::T,    IN::T, IN::T,    IN::T, IN::T, /*4*/ \
	IN::T, IN::T,    IN::T, IN::T,    IN::T, IN::T,    IN::T, IN::T,    IN::T, IN::T,    IN::F, IN::A,    IN::A, IN::A,    IN::F, IN::F, /*5*/ \
	IN::T, IN::T,    IN::T, IN::T,    IN::T, IN::T,    IN::T, IN::T,    IN::T, IN::T,    IN::T, IN::T,    IN::T, IN::T,    IN::T, IN::T, /*6*/ \
	IN::T, IN::T,    IN::T, IN::T,    IN::T, IN::T,    IN::T, IN::T,    IN::T, IN::T,    IN::T, IN::A,    IN::A, IN::A,    IN::F, IN::F, /*7*/ \
																																			   \
	IN::T, IN::T,    IN::T, IN::F,    IN::F, IN::F,    IN::F, IN::F,    IN::F, IN::F,    IN::F, IN::F,    IN::F, IN::F,    IN::F, IN::F, /*8*/ \
	IN::F, IN::F,    IN::F, IN::F,    IN::F, IN::F,    IN::F, IN::T,    IN::F, IN::F,    IN::F, IN::F,    IN::F, IN::F,    IN::F, IN::F, /*9*/ \
	IN::F, IN::F,    IN::F, IN::F,    IN::F, IN::F,    IN::F, IN::F,    IN::F, IN::F,    IN::F, IN::F,    IN::F, IN::F,    IN::F, IN::F, /*10*/\
	IN::F, IN::F,    IN::F, IN::F,    IN::F, IN::F,    IN::F, IN::F,    IN::F, IN::F,    IN::F, IN::F,    IN::F, IN::F,    IN::F, IN::F, /*11*/\
	IN::F, IN::F,    IN::F, IN::F,    IN::F, IN::F,    IN::F, IN::T,    IN::F, IN::F,    IN::F, IN::F,    IN::F, IN::F,    IN::F, IN::F, /*12*/\
	IN::F, IN::F,    IN::F, IN::F,    IN::F, IN::F,    IN::F, IN::F,    IN::F, IN::F,    IN::F, IN::F,    IN::F, IN::F,    IN::F, IN::T, /*13*/\
	IN::F, IN::T,    IN::F, IN::F,    IN::F, IN::F,    IN::F, IN::F,    IN::T, IN::F,    IN::F, IN::F,    IN::T, IN::F,    IN::F, IN::F, /*14*/\
	IN::F, IN::F,    IN::F, IN::F,    IN::F, IN::F,    IN::F, IN::T,    IN::F, IN::F,    IN::F, IN::F,    IN::F, IN::F,    IN::F, IN::F  /*15*/\
}

namespace In
{
	struct IN
	{
		enum { T = 1024, F = 2048, I = 4096, A = 8192 }; //A: space, $, %, ', (, ), *, +, , , -, ., /, ;, :, <, =, >, [, ], \, {, }, |, tab, line field, vertical tab...
		int size;
		int file_size;
		int lines;
		int ignor;
		unsigned char* text;
		int code[256];
	};

	IN getIn(wchar_t infile[], wchar_t outfile[]);
}

