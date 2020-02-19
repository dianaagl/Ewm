
#include "memory.h"
#include<QDebug>


Memory::Memory(int cond, int k)
{
    this->key = k;
    this->cond = cond;
    val = new QString("");

    key_update();

}

Memory::Memory(int k)
{
    Memory(2, k);

}

Memory::~Memory()
{
    delete val;
}

void Memory::set_key(int k)
{
    key = k;
    key_update();
}

void Memory::to_bin()
{

    cond = 0;

    QString* str = new QString("");
    int k = this->key;

    for (int j = 0; j < 16; j++)
    {
        (*str) = ('0'+(k%2)) + (*str);
        k /= 2;
    }

    delete val;
    val = str;

}



void Memory::to_dec()
{
    //    mem_lineEdit->setMaxLength(5);

    cond = 1;

    char *s = new char [10];
    sprintf(s, "%d", key);

    delete val;
    val = new QString(s);

    delete []s;
}

void Memory::to_hex()
{
    //    mem_lineEdit->setMaxLength(4);

    cond = 2;

    QString *s = new QString("") ;
    int k = key;

    for (int j = 0; j < 4; j++)
    {
        int r = k%16;
        if (r > 9)
            (*s) = ('A' + (r-10)) + (*s);
        else
            (*s) = ('0'+r) + (*s);
        k /= 16;
    }
    delete val;
    val = s;


}

void Memory::to_bool()
{

    cond = 3;

    if (key == 0)
    {
        delete val;
        val = new QString("0");
    }
    else
    {
        delete val;
        val = new QString("1");
    }


}
void Memory::setVal(QString newVal)
{
    *val = newVal;
}

QString Memory::getVal()
{
   return *val;

}
void Memory::key_update()
{
    if (cond == 0)
        to_bin();
    else if (cond == 1)
        to_dec();
    else if (cond == 2)
        to_hex();
    else if (cond == 3)
        to_bool();
}

void Memory::key_get()
{
    QString * s =val;
    if (s->size() == 0)
    {
        set_key(0);
        return;
    }

    int k = 0;
    int d = 1;

    if (cond == 0)
        for (int i = (s)->size()-1; i >= 0; i--)
        {
            k = k + d*(int)((*s)[i].toLatin1()-'0');
            d *= 2;
        }
    else if (cond == 1 || cond == 3)
    {
        k = (*s).toInt();
        if (k >= (1<<16))
            k = (1<<16)-1;
    }
    else if (cond == 2)
        for (int i = (s)->size()-1; i >= 0; i--)
        {
            int r;
            if ((*s)[i].isNumber())
                r = (int)((*s)[i].toLatin1()-'0');
            else
                r = (int)((*s)[i].toUpper().toLatin1()-'A'+10);

            k = k + d*r;
            d *= 16;
        }

    key = k;



    if (cond == 0)
        to_bin();
    else if (cond == 1)
        to_dec();
    else if (cond == 2)
        to_hex();
    else if (cond == 3)
        to_bool();
}

