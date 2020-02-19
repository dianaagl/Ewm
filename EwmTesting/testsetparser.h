#ifndef TESTSETPARSER_H
#define TESTSETPARSER_H

#include <QMap>
#include <QString>
#include <QXmlStreamReader>





class TestsetParser  {

private:
    QString testText;
    bool  _isValid;
    QString comment;
    void parse();
    void parseTest(QXmlStreamReader &parser, int id);
    void parseTestData(QXmlStreamReader &parser, int id, int key);
    void parseTestAnswer(QXmlStreamReader &parser, int id, int key);
    int encriptArg(int val, int key);
    QRegExp *isTestMemoryContentReg, *isLabelNumberPointerReg, *isBit, *isTestLabelNumberPointerReg;
    QVector<QMap<QString, int> > tests, answers;
public:
    TestsetParser(QString testText);
    ~TestsetParser();
    QString getComment();
    int getTestCount();
    void getTest(int id, QMap<QString, int> &test, QMap<QString, int> &answer);
    bool isValid();
};



#endif // TESTSETPARSER_H
