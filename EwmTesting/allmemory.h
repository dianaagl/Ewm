#ifndef ALLMEMORY_H
#define ALLMEMORY_H

#include "memory.h"

#include <QStack>



class AllMemory
{
public:
    int n, m;
    Memory * memory;
    Memory * reg[6];
    QStack<QString> stack;
    AllMemory(int, int);
    ~AllMemory();
    void makeEmpty();
    void toCondition(int cond);
    void toConditionReg(int cond);
    void key_update();
private:





};

#endif // ALLMEMORY_H
