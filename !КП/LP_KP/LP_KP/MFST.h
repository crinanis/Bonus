#pragma once

#include "GBR.h"
#include "LT.h"
#include <vector>

#define MFST_DIAGN_MAXSIZE 2*ERROR_MAX_SIZE_MESSAGE
#define MFST_DIAGN_NUMBER 3

#define MFST_TRACE_START std::cout<<std::setw( 4)<< std::left<<"Шаг"<< ':'		\
								  <<std::setw(20)<< std::left<<" Правило"		\
								  <<std::setw(30)<< std::left<<" Входная лента"	\
								  <<std::setw(20)<< std::left<<" Стек"			\
								  <<std::endl;

static int FST_TRACE_n = -1;
static char rbuf[205], sbuf[205], lbuf[1024];

#define MFST_TRACE1		std::cout<<std::setw(4)<<std::left<<++FST_TRACE_n<< ": "	\
									<<std::setw(20)<<std::left<<rule.getCRule(rbuf, nrulechain) \
									<<std::setw(30)<<std::left<<getCLenta(lbuf, lenta_position)	\
									<<std::setw(20)<<std::left<<getCSt(sbuf)	\
									<<std::endl;

#define MFST_TRACE2		std::cout<<std::setw(4)<<std::left<<FST_TRACE_n<< ": "	\
									<<std::setw(20)<<std::left<< " "	\
									<<std::setw(30)<<std::left<<getCLenta(lbuf, lenta_position)	\
									<<std::setw(20)<<std::left<<getCSt(sbuf)	\
									<<std::endl;

#define MFST_TRACE3		std::cout<<std::setw(4)<<std::left<<++FST_TRACE_n<< ": "	\
									<<std::setw(20)<<std::left<< " "	\
									<<std::setw(30)<<std::left<<getCLenta(lbuf, lenta_position)	\
									<<std::setw(20)<<std::left<<getCSt(sbuf)	\
									<<std::endl;

#define MFST_TRACE4(c) std::cout<<std::setw(4)<<std::left<<++FST_TRACE_n<< ": "<<std::setw(20)<<std::left<<c<<std::endl;

#define MFST_TRACE5(c) std::cout<<std::setw(4)<<std::left<<  FST_TRACE_n<< ": "<<std::setw(20)<<std::left<<c<<std::endl;

#define MFST_TRACE6(c,k) std::cout<<std::setw(4)<<std::left<<  FST_TRACE_n<< ": "<<std::setw(20)<<std::left<<c<<k<<std::endl;

#define	MFST_TRACE7		 std::cout << std::setw(4) << std::left << state.lenta_position<<": "	\
									<<std::setw(20)<<std::left<<rule.getCRule(rbuf, state.nrulechain)	\
									<<std::endl;



using namespace std;
typedef vector<short> MFSTSTSTACK;


namespace MFST
{
	struct MfstState	// состояние автомата (для сохранения)
	{
		short lenta_position;
		short nrule;
		short nrulechain;		// номер текущей цепочки, текущего правила
		MFSTSTSTACK st;	// стек автомата

		MfstState();
		MfstState(short pposition, MFSTSTSTACK pst, short pnrulechain);
		MfstState(short pposition, MFSTSTSTACK pst, short pnrule, short pnrulechain);

	};

	struct Mfst // магазинный автомат
	{
		enum RC_STEP //код возврата функции step
		{
			NS_OK,			// найдено правило и цепочка, цепочка записана в стек 
			NS_NORULE,		// не найдено правило грамматики (ошибка в грамматике)
			NS_NORULECHAIN,	// не найдена походящая цепочка правила (ошибка в исходном коде)
			NS_ERROR,		// неизвесный нетерминальный символ грамматики
			TS_OK,			// тек. символ ленты == вершине стека, продвинулась лента, pop стека
			TS_NOK,			// тек. символ ленты != вершине стека, восстановленно состояние 
			LENTA_END,		// теущая позиция ленты >= lenta_size 
			SURPRISE		// неожиданный код возврата (ошибка в step)
		};

		struct MfstDiagnosis	// диагностика
		{
			short	lenta_position;		// позиция на ленте 
			RC_STEP	rc_step;			// код завершения шага 
			short	nrule;				// номер правила 
			short	nrule_chain;		// номер цепочки правила
			MfstDiagnosis();
			MfstDiagnosis(short plenta_position, RC_STEP prc_step, short pnrule, short pnrule_chain);
		} diagnosis[MFST_DIAGN_NUMBER]; // последние самые глубокие сообщения

		GRBALPHABET* lenta;					// перекодированная (TS/NS) лента (из LEX)
		short lenta_position;				// текущая позиция на ленте
		short nrule;						// номер текущего правила
		short nrulechain;					// номер текущей цепочки, текущего правила
		short lenta_size;					// размер ленты
		GRB::Greibach grebach;				// грамматика Грейбах
		LT::LexTable lexTable;
		MFSTSTSTACK st;					// стек автомата
		vector<MfstState> storestate;	// стек для сохранения состояний

		Mfst();
		Mfst(LT::LexTable& plexTable, GRB::Greibach pgrebach);

		char* getCSt(char* buf);			//получить содержиое стека
		char* getCLenta(char* buf, short pos, short n = 25);	//лента: n символов, начиная с pos
		char* getDiagnosis(short n, char* buf);		//получить n-ую строку диагностики или '\0'

		bool savestate();	//сохранить состояние автомата
		bool resetstate();	//восстановить состояние автомата
		bool push_chain(GRB::Rule::Chain chain);

		RC_STEP step();		//выполнить шаг автомата
		bool start();		//запустить автомат
		bool savedDiagnosis(RC_STEP prc_step);

		void printRules();	//вывести последовательность правил

		struct Deducation
		{
			short size;
			short* nrules;
			short* nrulechains;

			Deducation()
			{
				this->size = 0;
				this->nrules = 0;
				this->nrulechains = 0;
			}
		} deducation;

		bool savededucation();
	};
}