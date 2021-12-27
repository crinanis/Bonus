#pragma once

#include "GBR.h"
#include "LT.h"
#include <vector>

#define MFST_DIAGN_MAXSIZE 2*ERROR_MAX_SIZE_MESSAGE
#define MFST_DIAGN_NUMBER 3

#define MFST_TRACE_START std::cout<<std::setw( 4)<< std::left<<"���"<< ':'		\
								  <<std::setw(20)<< std::left<<" �������"		\
								  <<std::setw(30)<< std::left<<" ������� �����"	\
								  <<std::setw(20)<< std::left<<" ����"			\
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
	struct MfstState	// ��������� �������� (��� ����������)
	{
		short lenta_position;
		short nrule;
		short nrulechain;		// ����� ������� �������, �������� �������
		MFSTSTSTACK st;	// ���� ��������

		MfstState();
		MfstState(short pposition, MFSTSTSTACK pst, short pnrulechain);
		MfstState(short pposition, MFSTSTSTACK pst, short pnrule, short pnrulechain);

	};

	struct Mfst // ���������� �������
	{
		enum RC_STEP //��� �������� ������� step
		{
			NS_OK,			// ������� ������� � �������, ������� �������� � ���� 
			NS_NORULE,		// �� ������� ������� ���������� (������ � ����������)
			NS_NORULECHAIN,	// �� ������� ��������� ������� ������� (������ � �������� ����)
			NS_ERROR,		// ���������� �������������� ������ ����������
			TS_OK,			// ���. ������ ����� == ������� �����, ������������ �����, pop �����
			TS_NOK,			// ���. ������ ����� != ������� �����, �������������� ��������� 
			LENTA_END,		// ������ ������� ����� >= lenta_size 
			SURPRISE		// ����������� ��� �������� (������ � step)
		};

		struct MfstDiagnosis	// �����������
		{
			short	lenta_position;		// ������� �� ����� 
			RC_STEP	rc_step;			// ��� ���������� ���� 
			short	nrule;				// ����� ������� 
			short	nrule_chain;		// ����� ������� �������
			MfstDiagnosis();
			MfstDiagnosis(short plenta_position, RC_STEP prc_step, short pnrule, short pnrule_chain);
		} diagnosis[MFST_DIAGN_NUMBER]; // ��������� ����� �������� ���������

		GRBALPHABET* lenta;					// ���������������� (TS/NS) ����� (�� LEX)
		short lenta_position;				// ������� ������� �� �����
		short nrule;						// ����� �������� �������
		short nrulechain;					// ����� ������� �������, �������� �������
		short lenta_size;					// ������ �����
		GRB::Greibach grebach;				// ���������� �������
		LT::LexTable lexTable;
		MFSTSTSTACK st;					// ���� ��������
		vector<MfstState> storestate;	// ���� ��� ���������� ���������

		Mfst();
		Mfst(LT::LexTable& plexTable, GRB::Greibach pgrebach);

		char* getCSt(char* buf);			//�������� ��������� �����
		char* getCLenta(char* buf, short pos, short n = 25);	//�����: n ��������, ������� � pos
		char* getDiagnosis(short n, char* buf);		//�������� n-�� ������ ����������� ��� '\0'

		bool savestate();	//��������� ��������� ��������
		bool resetstate();	//������������ ��������� ��������
		bool push_chain(GRB::Rule::Chain chain);

		RC_STEP step();		//��������� ��� ��������
		bool start();		//��������� �������
		bool savedDiagnosis(RC_STEP prc_step);

		void printRules();	//������� ������������������ ������

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