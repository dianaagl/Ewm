#include "allmemory.h"


AllMemory::AllMemory(int n, int m)
{
    this->n = n;
    this->m = m;
    memory = new Memory[(1<<16)];
    reg[0] = new Memory( 1, 0);
    reg[1] = new Memory( 1, 0);
    reg[2] = new Memory( 1, 0);
    reg[3] = new Memory( 1, 0);
    reg[4] = new Memory( 3, 0);
    reg[5] = new Memory( 3, 0);
    stack = QStack<QString>();

}

void AllMemory::makeEmpty(){

}
void AllMemory::key_update()
{
    for (int i = 0; i < 6; i++)
    {
        reg[i]->key_update();
    }
}
void AllMemory::toCondition(int cond){
    if (cond == 0)
    {
        for(int i = 0;i < 1 << 16;i++){
            memory[i].to_bin();
        }

    }

    else if (cond == 1)
    {
        for(int i = 0;i < 1 << 16;i++){
            memory[i].to_dec();
        }

    }
    else if (cond == 2)
    {
        for(int i = 0;i < 1 << 16;i++){
            memory[i].to_hex();
        }

    }

}
void AllMemory::toConditionReg(int cond){
    if (cond == 0)
    {

        for(int i = 0;i < 4;i++){
            reg[i]->to_bin();
        }
    }

    else if (cond == 1)
    {
        for(int i = 0;i < 4;i++){
            reg[i]->to_dec();
        }
    }
    else if (cond == 2)
    {
        for(int i = 0;i < 4;i++){
            reg[i]->to_hex();
        }
    }
    else if (cond == 3)
    {
        for(int i = 4;i < 6;i++){
            reg[i]->to_bin();
        }

    }

}

AllMemory::~AllMemory()
{
    delete [] memory;
    for(auto &i:reg){
        delete i;
    }


}
