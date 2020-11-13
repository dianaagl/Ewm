#include <QCoreApplication>
#include "ewmtesting.h"
#include <stdio.h>
#include <QDir>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    EwmTesting * test;
    test = new EwmTesting(argv[1], argv[2]);
    test->startTesting();

    return a.exec();
}
