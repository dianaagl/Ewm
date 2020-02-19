#ifndef PROGARAMM_H
#define PROGARAMM_H
#include<QDebug>
#include <QMap>
#include <QString>
#include <QStringList>
#include <QVector>
#include "allmemory.h"
#include "functions.h"
#include "memory.h"

#define BEGIN_CONST 48
#define END_CONST 49
#define DOT_CONST 50
#define LABEL_NUMBER_POINTER 52
#define LABEL_WORD 52
#define LABEL_WORD_POINTER 53
#define TIME_LIMIT 1
class Progaramm
{
public:
    Progaramm(QString, AllMemory*);
    Progaramm(AllMemory*);
    void compile();
    void setCodeText( QString value);
    bool isCompiled();
    void initMemory(AllMemory*);
    void setCompiled(bool flag);
    int lineCount;
    int currLine;

    QVector <QString> commandString;
    QVector <int> commandInt;
    QVector <int> lineNumber; /* obtain the number of first command of [i] line */

    QMap <int, int> labelMap;
    Memory *get_operand(int);

     QRegExp *isSpaceReg, *isMemoryContentReg, *isTestMemoryContentReg, *isArrayPointerReg;
     QRegExp *isLabelNumberPointerReg;
     QRegExp *isLabelWordReg, *isLabelWordPointerReg;
     QString getCodeText() ;
     QStringList *errorWindow;
     void print(QString str);
private:

     bool compiled;
     int commandCount;
     AllMemory * allMemory;
     QString codeText;
     QStringList lineList, line;
     QVector <int> commandLine;
};

#endif // PROGARAMM_H
