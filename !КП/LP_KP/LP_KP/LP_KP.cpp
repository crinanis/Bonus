#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[])
{
    setlocale(LC_ALL, "Rus");
    Log::LOG log = Log::INITLOG;
    try
    {   
        Parm::PARM parm = Parm::getParm(argc, argv);
        log = Log::getlog(parm.log);
        Log::WriteLine(log, (char*)"Тест:", (char*)"без ошибок", (char*)"");
        Log::WriteLog(log);
        Log::WriteParm(log, parm);
        In::IN in = In::getIn(parm.in, parm.out);
        Log::WriteIn(log, in);

        LexTable lexTable = LT::Create(1000);   //1000000
        IdTable	idTable = IT::Create(1000);     //1000000
        /*IT::GetEntry(idTable, 500000);*/

        LA::LexAnalysis(in, lexTable, idTable);

        IT::PrintIdTable(idTable);

        MFST_TRACE_START
            MFST::Mfst mfst(lexTable, GRB::getGreibach());
        mfst.start();
        mfst.savededucation();
        mfst.printRules();

        SemAnalysis(lexTable, idTable);

        PolishNotation(lexTable, idTable);
        

        LT::Delete(lexTable);
        IT::Delete(idTable);

        Log::Close(log);
        

    }
    catch (Error::ERROR e)
    {
        Log::WriteError(log, e);
        cout << "\nОшибка " << e.id << ": " << e.message << ", строка " << e.inext.line + 1 << " символ " << e.inext.col << endl;
    };
    system("PAUSE");
    return 0;
}
