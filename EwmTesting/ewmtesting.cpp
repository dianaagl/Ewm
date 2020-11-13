#include "ewmtesting.h"
#include<QDebug>
#include <QDir>
#include <QFile>
#include <QTextStream>


EwmTesting::EwmTesting(QString  codeFilename, QString  testFileName)
{

    parser = NULL;
    allMemory = new AllMemory(64,8);
    prog = new Progaramm(allMemory);

    if (codeFilename.toStdString() != "") {
        QString str;

        QFile file( codeFilename);
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream *in;
        in = new QTextStream(&file);
        str = in->readAll();
        file.close();
        setProgramCode(str, codeFilename);
    }

    //prog->print(progText.toStdString().c_str());
    if (testFileName.toStdString() != "") {
        QString str;

        QFile file( testFileName);
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream *in;
        in = new QTextStream(&file);
        str = in->readAll();
        file.close();
        downloadTestset(str, testFileName);
    }

     timer.start();
}
EwmTesting::EwmTesting(){
    parser = NULL;
    allMemory = new AllMemory(64,8);
    prog = new Progaramm(allMemory);
    timer.start();
}
EwmTesting::~EwmTesting(){
    delete allMemory;
    delete prog;
}
bool EwmTesting::isCorrect(QMap<QString, int> *answer) {
    bool isOK = true;
    for (QMap<QString, int>::Iterator it = answer->begin(); it != answer->end(); ++it) {
        if (it.key() == "AX") {
            isOK &= (allMemory->reg[0]->key == it.value());
            //qDebug() << "AX " << allMemory->reg[1]->key << " " << it.value() << endl;
        }
        else if (it.key() == "BX") {
            isOK &= (allMemory->reg[1]->key == it.value());
        }
        else if (it.key() == "CX") {
            isOK &= (allMemory->reg[2]->key == it.value());
        }
        else if (it.key() == "DX") {
            isOK &= (allMemory->reg[3]->key == it.value());
        }
        else if (it.key() == "Z") {
            isOK &= (allMemory->reg[4]->key == it.value());
        }
        else if (it.key() == "C") {
            isOK &= (allMemory->reg[5]->key == it.value());
        }
        else if (prog->isTestMemoryContentReg->exactMatch(it.key())) {
            isOK &= (allMemory->memory[it.key().right(it.key().size() - 3).toInt()].key == it.value());
        }
    }
    return isOK;
}

bool EwmTesting::downloadTestset(QString tmpTestText, QString fileName)
{
        if(parser != NULL) delete parser;
        parser = new TestsetParser(tmpTestText);
        if (!parser->isValid()) {
            prog->print("Testset is invalid. Nothing be done.");
            prog->print(parser->getComment());
            testText = "";
            return false;
        }

        testText = tmpTestText;
        prog->print("Testset downloaded from "  + fileName);
        return true;
}
bool EwmTesting::startTesting()
{
    prog->compile();

    if (!prog->isCompiled()) {
        prog->print("Some errors in project");
        return false;
    }
    if (testText == "") {
        prog->print("testset wasn't downloaded.");
        return false;
    }
    else {
        prog->print("Testing on testset from: "+ testPath);
    }
    QMap<QString, int> test, answer, testWithWA;
    bool isOK = true;
    for (int i = 0; i < parser->getTestCount(); ++i) {

        parser->getTest(i, test, answer);
        initMemory(&test);

        startTime = timer.elapsed();
        prog->currLine = 1;
        while (prog->currLine < prog->lineCount-1) {
            if(!makeStep()) {
                isOK = false;
                prog->print(("Test "+ QString::number(i + 1) + ": RE").toStdString().c_str());
                break;
            }
            if ((timer.elapsed()-startTime)/1000 > TIME_LIMIT) {
                isOK = false;
                prog->print(("Test " + QString::number(i + 1) + ": TL").toStdString().c_str());
                break;
            }
        }

        if (!isCorrect(&answer)) {
            if (isOK) testWithWA = test;
            isOK = false;
            prog->print(("Test " + QString::number(i + 1) + ": WA").toStdString().c_str());
        }
        else {
            prog->print(("Test " + QString::number(i + 1) + ": OK").toStdString().c_str());
        }
    }
    isOK ? prog->print("OK Solution is correct.") : prog->print("Testing is unsuccessful.");
    if (!isOK) {
        initMemory(NULL);
        initMemory(&testWithWA);
    }
    else {
        initMemory(NULL);
    }
    return true;

}
bool EwmTesting::setProgramCode(QString  str, QString filename){

        prog->setCodeText(str);
        prog->print("Program downloaded from " + filename);
        return true;
}

void EwmTesting::saveProgram(QString codeText)
{
//    QFile file(testPath);
//    file.open(QIODevice::WriteOnly | QIODevice::Text);
//    QTextStream out(&file);
//    out << codeText;
//    prog->setCodeText(codeText);
//    file.close();
}

void EwmTesting::initMemory(QMap<QString, int>  *test ) {
    int index = 0;
    for (int i = 0; i < (1 << 16); ++i)
        allMemory->memory[i].set_key(0);
    for (int i = 0; i < 5; ++i)
        allMemory->reg[i]->set_key(0);
    if (test != NULL) {
        for (QMap<QString, int>::Iterator it = test->begin(); it != test->end(); ++it) {
            if (it.key() == "AX") {
                allMemory->reg[0]->set_key(it.value());
            }
            else if (it.key() == "BX") {
                allMemory->reg[1]->set_key(it.value());
            }
            else if (it.key() == "CX") {
                allMemory->reg[2]->set_key(it.value());
            }
            else if (it.key() == "DX") {
                allMemory->reg[3]->set_key(it.value());
            }
            else if (it.key() == "Z") {
                allMemory->reg[4]->set_key(it.value());
            }
            else if (it.key() == "C") {
                allMemory->reg[5]->set_key(it.value());
            }
            else if (prog->isTestMemoryContentReg->exactMatch(it.key())) {
                index = it.key().right(it.key().size() - 3).toInt();
                allMemory->memory[index].set_key(it.value());


           }
            //qDebug() << it.key() << endl;
        }
    }

    return;
}

bool EwmTesting::makeStep()
{
    if (!prog->isCompiled())
    {
        prog->print("Project wasn't compiled;");
        return false;
    }

    if (prog->currLine >= (prog->lineCount-1))
    {

        prog->currLine = 1;

        return true;
    }

    int d = prog->currLine+1;
    int i = prog->lineNumber[prog->currLine];

    while (i < prog->lineNumber[prog->currLine+1])
    {
        int comm = prog->commandInt[i];
        int res;

        Memory *oper1, *oper2;

        if (comm <= 8)
        {
            oper1 = prog->get_operand(prog->commandInt[i+1]);

            res = oper1->key;

            if (comm == 1)
            {
                res = (-(oper1->key)+(1<<16))%(1<<16);

                if (res == 0)
                    allMemory->reg[5]->set_key(1);
                else
                    allMemory->reg[5]->set_key(0);

            }
            else if (comm == 2)
            {
                res--;
                if (res < 0)
                    res += (1<<16);

                if (res == 0)
                    allMemory->reg[5]->set_key(1);
                else
                    allMemory->reg[5]->set_key(0);
            }
            else if (comm == 3)
            {
                res = (res + 1)%(1<<16);


                if (res == 0)
                    allMemory->reg[5]->set_key(1);
                else
                    allMemory->reg[5]->set_key(0);
            }
            else if (comm == 4)
                res = ((res)^((1<<16)-1));
            else if (comm == 5)
            {
                int newc = res/(1<<15);
                res = (res<<1)%(1<<16)+allMemory->reg[4]->key;
                allMemory->reg[4]->set_key(newc);
            }
            else if (comm == 6)
            {
                int newc = res%2;
                res = (res>>1) + (1<<15)*allMemory->reg[4]->key;
                allMemory->reg[4]->set_key(newc);
            }
            else if (comm == 7)
            {
                if (allMemory->stack.size() > 0)
                    res = hextoint(allMemory->stack.pop());
                else
                {
                    prog->print(inttohex(prog->currLine) +": Error: stack is empty;");

                    prog->currLine = 1;

                    allMemory->stack.clear();
                    isStackEmpty = true;
                    return false;
                }
            }
            else if (comm == 8)
            {
                allMemory->stack.push(inttohex(oper1->key));
            }

            oper1->set_key(res);

            i += 2;
        }

        if (comm >= 9 && comm <= 16)
        {
            oper1 = prog->get_operand(prog->commandInt[i+1]);
            oper2 = prog->get_operand(prog->commandInt[i+3]);

            if (oper2 == 0)
                oper2 = new Memory(2, hextoint(prog->commandString[i+3]));

            res = oper1->key;

            if (comm == 9)
            {
                res += oper2->key;

                allMemory->reg[4]->set_key(res/(1<<16));
                res %= (1<<16);

                allMemory->reg[5]->set_key(0);
                if (res == 0)
                    allMemory->reg[5]->set_key(1);
            }
            else if (comm == 10)
            {
                res -= oper2->key;

                if (res >= 0)
                    allMemory->reg[4]->set_key(0);
                if (res < 0)
                {
                    allMemory->reg[4]->set_key(1);
                    res += (1<<16);
                }

                if (res != 0)
                    allMemory->reg[5]->set_key(0);
                if (res == 0)
                    allMemory->reg[5]->set_key(1);
            }
            else if (comm == 11)
            {
                res += oper2->key + allMemory->reg[4]->key;

                allMemory->reg[4]->set_key(res/(1<<16));
                res %= (1<<16);

                allMemory->reg[5]->set_key(0);
                if (res == 0)
                    allMemory->reg[5]->set_key(1);
            }
            else if (comm == 12)
            {
                res -= (oper2->key + allMemory->reg[4]->key);

                if (res >= 0)
                    allMemory->reg[4]->set_key(0);
                if (res < 0)
                {
                    allMemory->reg[4]->set_key(1);
                    res += (1<<16);
                }

                if (res != 0)
                    allMemory->reg[5]->set_key(0);
                if (res == 0)
                    allMemory->reg[5]->set_key(1);
            }
            else if (comm == 13)
                res = oper2->key;
            else if (comm == 14)
            {
                res -= oper2->key;

                if (res >= 0)
                    allMemory->reg[4]->set_key(0);
                if (res < 0)
                {
                    allMemory->reg[4]->set_key(1);
                    res += (1<<16);
                }

                if (res != 0)
                    allMemory->reg[5]->set_key(0);
                if (res == 0)
                    allMemory->reg[5]->set_key(1);

                res = oper1->key;
            }
            else if (comm == 15)
            {
                res &= oper2->key;

                if (res != 0)
                    allMemory->reg[5]->set_key(0);
                if (res == 0)
                    allMemory->reg[5]->set_key(1);

                allMemory->reg[4]->set_key(0);
            }
            else if (comm == 16)
            {
                res |= oper2->key;

                if (res != 0)
                    allMemory->reg[5]->set_key(0);
                if (res == 0)
                    allMemory->reg[5]->set_key(1);

                allMemory->reg[4]->set_key(0);
            }

            oper1->set_key(res);

            i += 4;
        }

        if (comm >= 17 && comm <= 19)
        {
            if (comm == 17)
                allMemory->reg[4]->set_key(0);
            else if (comm == 18)
                allMemory->reg[4]->set_key(1);
            else if (comm == 19)
                allMemory->reg[4]->set_key((allMemory->reg[4]->key + 1)%2);

            i += 1;
        }

        if (comm >= 20 && comm <= 26)
        {
            int d1=-1; // Init d1
            if (prog->commandInt[i+1] == LABEL_NUMBER_POINTER)
                d1 = hextoint(prog->commandString[i+1]);
            else if (prog->commandInt[i+1] == LABEL_WORD_POINTER)
                d1 = prog->labelMap[hextoint(prog->commandString[i+1].mid(1))];

            if (comm == 20)
                d = d1;
            else if (comm == 21)
            {
                if (allMemory->reg[5]->key == 1)
                    d = d1;
            }
            else if (comm == 22)
            {
                if (allMemory->reg[5]->key == 0)
                    d = d1;
            }
            else if (comm == 23)
            {
                if (allMemory->reg[4]->key == 1)
                    d = d1;
            }
            else if (comm == 24)
            {
                if (allMemory->reg[4]->key == 0)
                    d = d1;
            }
            else if (comm == 25)
            {
                int res = allMemory->reg[2]->key;
                res--;
                if (res < 0)
                    res += (1<<16);

                allMemory->reg[2]->set_key(res);
                if (res != 0)
                    d = d1;
            }
            else if (comm == 26)
            {
                allMemory->stack.push(inttohex(d));
                d = d1;
            }

            i += 2;
        }

        if (comm == 27)
        {
            if (allMemory->stack.size() != 0)
                d = hextoint(allMemory->stack.pop());
            else
            {
                prog->print(inttohex(prog->currLine) + ": Error: allMemory->stack is empty;");

                prog->currLine = 1;

                allMemory->makeEmpty();
                isStackEmpty = true;
                return false;
            }
            i += 1;
        }

        if (comm == LABEL_WORD)
            i += 1;
    }

//    allmemory->memory[1].set_key(stack.size());
//    allmemory->memory[0].set_key(d);

    if (d >= prog->lineCount || d == 0)
    {
        prog->print(inttohex(prog->currLine) +": Label over code in process;");

        return false;
    }

    prog->currLine = d;

    return true;
}

AllMemory * EwmTesting::getMemoryTable(int cond)
{
   allMemory->toCondition(cond);
   return allMemory;
}

QString EwmTesting::getProgramCode()
{
    return prog->getCodeText();
}
