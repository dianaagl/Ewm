#include "functions.h"

int hextoint(QString s)
{
    int k = 0;
    int d = 1;
    for (int i = s.size()-1; i >= 0; i--)
    {
        if (s[i].isDigit())
            k += d*(s[i].toLatin1() - '0');
        else
            k += d*(s[i].toLatin1() - 'A' + 10);

        d *= 16;
    }

    return k;
}

QString inttohex(int k)
{
    QString s = "";

    for (int i = 0; i < 4; i++)
    {
        if (k%16 < 10)
            s = ('0'+ k%16) + s;
        else
            s = ('A' + k%16-10) + s;

        k /= 16;
    }
    return s;
}


QString inttostr(int k)
{
    QString s = "";
    s.setNum(k);
    return s;
}
