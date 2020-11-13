
#include "progaramm.h"
void Progaramm::print(QString str){
    errorWindow->append(str);
}
Progaramm::Progaramm(QString  codeText, AllMemory * allMemory)
{
    /*----------------------QRegExp------------------------*/
    isSpaceReg = new QRegExp("\\s");
    isMemoryContentReg = new QRegExp("^\\[[0-9A-F]{1,4}\\]$");
    isArrayPointerReg = new QRegExp("^[0-9A-F]{1,4}\\([A-D]{1,1}X\\)$");
    isLabelNumberPointerReg = new QRegExp("^[0-9A-F]{1,4}$");
    isTestMemoryContentReg = new QRegExp("^Mem([0-9]{1,5})$");
    isLabelWordPointerReg = new QRegExp("^\\?[0-9A-F]{1,4}$");
    isLabelWordReg = new QRegExp("^\\?[0-9A-F]{1,4}\\:$");

    /*----------------------- VIEW ------------------------*/

    this->codeText = codeText;
    this->allMemory = allMemory;
    errorWindow = new QStringList();
    compiled = false;
}
Progaramm::Progaramm(AllMemory* mem)
{
    /*----------------------QRegExp------------------------*/
    isSpaceReg = new QRegExp("\\s");
    isMemoryContentReg = new QRegExp("^\\[[0-9A-F]{1,4}\\]$");
    isArrayPointerReg = new QRegExp("^[0-9A-F]{1,4}\\([A-D]{1,1}X\\)$");
    isLabelNumberPointerReg = new QRegExp("^[0-9A-F]{1,4}$");
    isTestMemoryContentReg = new QRegExp("^Mem([0-9]{1,5})$");
    isLabelWordPointerReg = new QRegExp("^\\?[0-9A-F]{1,4}$");
    isLabelWordReg = new QRegExp("^\\?[0-9A-F]{1,4}\\:$");

    /*----------------------- VIEW ------------------------*/

    this->allMemory = mem;
    errorWindow = new QStringList();
    compiled = false;


}
void Progaramm::initMemory(AllMemory * allMemory){
    this->allMemory = allMemory;
}


bool Progaramm::isCompiled(){
    return compiled;
}

void Progaramm::compile()
{
    if(compiled) return;
    commandString.clear();
    commandInt.clear();
    lineNumber.clear();
    errorWindow->clear();
    allMemory->stack.clear();
    labelMap.clear();
    commandLine.clear();
    compiled = true;

    currLine = 1;

    codeText = codeText.toUpper();

    if (!codeText.endsWith("END"))
        codeText += " \nEND";

   if (!codeText.startsWith("BEGIN"))
        codeText = "BEGIN\n" + codeText;

    codeText.replace(": ", ":");
    codeText.replace(" , ", ",");

    codeText.replace(":", ": ");
    codeText.replace(",", " , ");
    codeText.replace("\0", "");

    lineList = codeText.split("\n");
    lineCount = lineList.size();

    for (int i = 0; i < lineCount; i++)
    {
        lineNumber.push_back(-1);

        line = lineList.at(i).split( *isSpaceReg, QString::SkipEmptyParts);

        for (int j = 0; j < line.size(); j++)
        {
            if (lineNumber[i] == -1)
                lineNumber[i] = commandString.size();

            commandString.push_back(line[j]);
            commandLine.push_back(i);
            commandInt.push_back(-1);
        }
    }

    for (int i = lineCount-2; i > 0; i--)
        if (lineNumber[i] == -1)
            lineNumber[i] = lineNumber[i+1];

    commandCount = commandString.size();

    for (int i = 0; i < commandCount; i++)
    {
        if (commandString[i] == "BEGIN")
            commandInt[i] = BEGIN_CONST;
        else if (commandString[i] == "END")
            commandInt[i] = END_CONST;
        else if (commandString[i] == "NEG")
            commandInt[i] = 1;
        else if (commandString[i] == "DEC")
            commandInt[i] = 2;
        else if (commandString[i] == "INC")
            commandInt[i] = 3;
        else if (commandString[i] == "NOT")
            commandInt[i] = 4;
        else if (commandString[i] == "RCL")
            commandInt[i] = 5;
        else if (commandString[i] == "RCR")
            commandInt[i] = 6;
        else if (commandString[i] == "POP")
            commandInt[i] = 7;
        else if (commandString[i] == "PUSH")
            commandInt[i] = 8;
        else if (commandString[i] == "ADD")
            commandInt[i] = 9;
        else if (commandString[i] == "SUB")
            commandInt[i] = 10;
        else if (commandString[i] == "ADC")
            commandInt[i] = 11;
        else if (commandString[i] == "SBB")
            commandInt[i] = 12;
        else if (commandString[i] == "MOV")
            commandInt[i] = 13;
        else if (commandString[i] == "CMP")
            commandInt[i] = 14;
        else if (commandString[i] == "AND")
            commandInt[i] = 15;
        else if (commandString[i] == "OR")
            commandInt[i] = 16;
        else if (commandString[i] == "CLC")
            commandInt[i] = 17;
        else if (commandString[i] == "STC")
            commandInt[i] = 18;
        else if (commandString[i] == "CMC")
            commandInt[i] = 19;
        else if (commandString[i] == "JMP")
            commandInt[i] = 20;
        else if (commandString[i] == "JZ")
            commandInt[i] = 21;
        else if (commandString[i] == "JNZ")
            commandInt[i] = 22;
        else if (commandString[i] == "JC")
            commandInt[i] = 23;
        else if (commandString[i] == "JNC")
            commandInt[i] = 24;
        else if (commandString[i] == "LOOP")
            commandInt[i] = 25;
        else if (commandString[i] == "CALL")
            commandInt[i] = 26;
        else if (commandString[i] == "RET")
            commandInt[i] = 27;
        else if (commandString[i] == "AX")
            commandInt[i] = 28;
        else if (commandString[i] == "BX")
            commandInt[i] = 29;
        else if (commandString[i] == "CX")
            commandInt[i] = 30;
        else if (commandString[i] == "DX")
            commandInt[i] = 31;
        else if (commandString[i] == "[AX]")
            commandInt[i] = 128;
        else if (commandString[i] == "[BX]")
            commandInt[i] = 129;
        else if (commandString[i] == "[CX]")
            commandInt[i] = 130;
        else if (commandString[i] == "[DX]")
            commandInt[i] = 131;
        else if (isMemoryContentReg->exactMatch(commandString[i]))
            commandInt[i] = 200+hextoint(commandString[i].mid(1, commandString[i].size()-2));
        else if (isArrayPointerReg->exactMatch(commandString[i]))
            commandInt[i] = -
(commandString[i][commandString[i].indexOf("(")+1].toLatin1()-'A' + 1
 + 16*hextoint(commandString[i].mid(0, commandString[i].indexOf("("))));
        else if (isLabelNumberPointerReg->exactMatch(commandString[i]))
        {
            commandInt[i] = LABEL_NUMBER_POINTER;
        }
        else if (isLabelWordReg->exactMatch(commandString[i]))
        {
            commandInt[i] = LABEL_WORD;
            if (labelMap.find(hextoint(commandString[i].mid(1, commandString[i].size()-2))) != labelMap.end())
            {
                print(inttohex(commandLine[i])+": Too many matches for one label;");
                compiled = false;
            }
            labelMap[hextoint(commandString[i].mid(1, commandString[i].size()-2))] = commandLine[i];
        }
        else if (isLabelWordPointerReg->exactMatch(commandString[i]))
            commandInt[i] = LABEL_WORD_POINTER;
        else if (commandString[i] == ",")
            commandInt[i] = DOT_CONST;
        else
        {
            print(inttohex(commandLine[i])+ ": Wrong command;");
            compiled = false;
        }
    }

    if (!compiled)
        return;

    for (int i = 1; i < lineCount-1; i++)
    {
        if ((commandInt[lineNumber[i]] < 1 || commandInt[lineNumber[i]] > 27) && commandInt[lineNumber[i]] != LABEL_WORD
            && commandInt[lineNumber[i]] != END_CONST)
        {
            print(inttohex(i) + ": Wrong line syntax;");
            compiled = false;
        }
    }

    if (!compiled)
        return;

    commandString.push_back("END");
    commandInt.push_back(END_CONST);
    commandString.push_back("END");
    commandInt.push_back(END_CONST);

    int t = 1;
    int prev_line = 0;
    int now_line = 0;
    while (t < commandCount-1)
    {
        prev_line = now_line;
        now_line = commandLine[t];
        if (commandInt[t] == LABEL_WORD)
        {
            if (now_line == prev_line)
            {
                print(inttohex(now_line)+": Label after funtion;");
                compiled = false;
            }

            t++;
        }
        else if (commandInt[t] < 1 || commandInt[t] > 27)
        {
            print(inttohex(now_line)+": Missed function or a lot of operands;");
            compiled = false;

            t++;
        }
        else
        {

            if (t - lineNumber[commandLine[t]] > 1 || (t - lineNumber[commandLine[t]] == 1 && commandInt[t-1] != LABEL_WORD))
            {
                print(inttohex(now_line)+": Few operators in line;");
                compiled = false;
            }

            if (commandInt[t] <= 8)
            {
                if (get_operand(commandInt[t+1]) == 0)
                {
                    print(inttohex(now_line)+": Missed operand;");
                    compiled = false;
                }

                t += 2;
            }
            else if (commandInt[t] <= 16)
            {
                if (get_operand(commandInt[t+1]) == 0)
                {
                    print(inttohex(now_line)+": Missed first operand;");
                    compiled = false;
                }

                if (commandInt[t+2] != DOT_CONST)
                {
                    print(inttohex(now_line)+": Missed comma;");
                    compiled = false;
                }

                if (get_operand(commandInt[t+3]) == 0)
                {
                    if (!isLabelNumberPointerReg->exactMatch(commandString[t+3]))
                    {
                        print(inttohex(now_line)+": Missed second operand;");
                        compiled = false;
                    }
                }

                t += 4;
            }
            else if (commandInt[t] <= 19)
            {
                t += 1;
            }
            else if (commandInt[t] <= 26)
            {
                if (commandInt[t+1] != LABEL_WORD_POINTER && commandInt[t+1] != LABEL_NUMBER_POINTER)
                {
                    print(inttohex(now_line)+": Wrong label syntax;");
                    compiled = false;
                }
                else if (commandInt[t+1] == LABEL_NUMBER_POINTER && (hextoint(commandString[t+1]) >= lineCount || hextoint(commandString[t+1]) == 0))
                {
                    print(inttohex(commandLine[t+1])+": Label over code;");
                    compiled = false;
                }

                t += 2;
            }
            else if (commandInt[t] == 27)
            {
                t += 1;
            }
        }
    }

    if(!compiled)
        return;

    for (int i = 1; i < commandCount; i++)
    {
        if (commandInt[i] == LABEL_WORD_POINTER)
        {
            if (labelMap.find(hextoint(commandString[i].mid(1))) == labelMap.end())
            {
                print(inttohex(commandLine[i])+": No matches for label;");
                compiled = false;
            }
            else
            {
                commandString[i] = inttohex(labelMap[hextoint(commandString[i].mid(1))]);
                commandInt[i] = LABEL_NUMBER_POINTER;
            }
        }
    }

    if (!compiled)
        return;

}

void Progaramm::setCompiled(bool flag)
{
    compiled = flag;
}

QString Progaramm::getCodeText()
{
    if (codeText.startsWith("BEGIN\n"))
         codeText.replace("BEGIN\n","");
    return codeText;
}

void Progaramm::setCodeText( QString value)
{
    codeText = value;
    compiled = false;
}
Memory *Progaramm::get_operand(int k)
{
    if (k >= 28 && k <= 31)  /* registers e.g. 'AX' */
        return (allMemory->reg[k-28]);
    else if (k >= 128 && k <= 131){ /* register is a pointer e.g. '[AX]' */
        int ind = (allMemory->reg[k-128]->key);
        if(ind < 0)
            return &(allMemory->memory[(1 << 16) + ind]);
        return &(allMemory->memory[ind]);
    }
    else if (k >= 200) /* memory e.g. [1000] */
        return &(this->allMemory->memory[k-200]);
    else if (k < 0) /* array e.g. (2)[CX] */{
        int ind2 = (allMemory->reg[(-k-1)%16]->key + (-k)/16)%(1<<16);
        if(ind2 < 0)
            ind2 = (1 << 16 )+ ind2;

        return &(this->allMemory->memory[ind2]);
}
    return 0;
}

