#ifndef MEMORY_H
#define MEMORY_H
#include <QString>



class Memory
{

public:
    Memory(int cond = 2, int k = 0);
    Memory(int);

    ~Memory();
    void set_key(int);
    int key;
    int cond; // 0 - bin, 1 - dec, 2 - hex, 3 - bool
    QString * val;

    void to_bin();
    void to_dec();
    void to_hex();
    void to_bool();
    void key_get();
    void key_update();
    void setVal(QString);
    QString getVal();

};


#endif // MEMORY_H
