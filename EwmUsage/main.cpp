#include <QCoreApplication>
#include "ewmtesting.h"
#include <stdio.h>
#include <QDir>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    EwmTesting * test;
 /*   char strs[3];
    strs[0] = 'a';
    strs[1] = 'b';
        strs[2] = 'c';
   char str[22],teststr[40];
    for(int i = 1;i < 5;i++){
        for(int j=0;j < 3;j++){
            sprintf (str, "/Users/diana/ewm/ewm2/solutions/%d%c.txt",  i,strs[j]);
            sprintf (teststr, "/Users/diana/ewm/ewm2/tests/%d%c.testset", i,strs[j]);

            test = new EwmTesting(str,teststr);
            test->startTesting();
            delete test;
        }
    }

*/
    qDebug() << argv[0];
    test = new EwmTesting(argv[1],argv[2]);
    test->startTesting();

    return a.exec();
}
