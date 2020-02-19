#ifndef EWM_TESTING_H
#define EWM_TESTING_H

#include "ewmtesting_global.h"



class EWM_TEST EwmTesting{
private:
    TestsetParser *parser;
    QString testText;
    QString tmpTestPath;
    int startTime;

    bool isCorrect(QMap<QString, int> *answer);



public:
    bool isStackEmpty = false;
    void initMemory(QMap<QString, int>  *test = NULL);
    EwmTesting(QString, QString );
    EwmTesting( );
    ~EwmTesting( );
    bool downloadTestset(QString);
    bool setProgramCode(QString);
    bool compile();
    bool startTesting();
    bool makeStep();
    QTime timer;
    AllMemory * allMemory;

    bool run();
    Memory* get_operand(int k);
    void saveProgram(QString);
    Progaramm * prog;


    AllMemory * getMemoryTable(int cond);
    QString getProgramCode();
    QString testPath;

};



#endif // EWM_TESTING_H
