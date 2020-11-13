

#include "testsetparser.h"
#include "functions.h"
#include <iostream>
#include <cstdlib>


TestsetParser::TestsetParser(QString _testText) {
    testText = _testText;


    isTestMemoryContentReg = new QRegExp("^Mem([0-9]{1,5})$");
    isLabelNumberPointerReg = new QRegExp("^[0-9]{1,5}$");
    isBit = new QRegExp("^(1|0)$");

    parse();
}

TestsetParser::~TestsetParser() {

}

bool TestsetParser::isValid() { //функция доступа
    return _isValid;
}

void TestsetParser::parse() { //читает данные всего testset
    _isValid = true;
    int id = 1;
    QXmlStreamReader parser(testText);

    parser.readNext();
    if (parser.tokenType() != QXmlStreamReader::StartDocument) {
        comment = "There isn't start tag.";
        _isValid = false;
        return;
    }
    parser.readNext();
    while (parser.tokenType() != QXmlStreamReader::StartElement && !parser.hasError() && _isValid)
        parser.readNext();
    if (parser.name() != "tests") {
        comment = "There isn't main tag";
        _isValid = false;
        return;
    }
    parser.readNext();
    while (!parser.atEnd() && _isValid && !parser.hasError() &&
           parser.tokenType() != QXmlStreamReader::StartElement) {
        parser.readNext();
    }
    while (!parser.atEnd() && _isValid && !parser.hasError() && parser.tokenType() != QXmlStreamReader::EndElement) {
        if (parser.tokenType() == QXmlStreamReader::StartElement && parser.name() != "test") {
            comment = "In test " + QString::number(id) + " Wrong tag:" + parser.name().toString() + " Expected test.";
            _isValid = false;
            return;
        }
        else if (parser.tokenType() == QXmlStreamReader::StartElement) {
            parseTest(parser, id);
            ++id;
        }
        parser.readNext();
    }
    //qDebug() << parser.name() << endl;
    parser.readNext();
    if (parser.hasError()) {
        comment = "Invalid xml.";
        _isValid = false;
    }
}

void TestsetParser::parseTest(QXmlStreamReader &parser, int id) { //читает данные из тега test
    int key = 0;
    QXmlStreamAttributes atributes = parser.attributes();
    if (atributes.hasAttribute("key")) {
        key = atributes.value("key").toString().toInt();
    }
    parser.readNext();
    while (!parser.atEnd() && !parser.hasError() && _isValid && parser.tokenType() != QXmlStreamReader::StartElement)
        parser.readNext();
    parseTestData(parser, id, key);
    while (!parser.atEnd() && !parser.hasError() && _isValid && parser.tokenType() != QXmlStreamReader::StartElement){
        parser.readNext();
    }
    parseTestAnswer(parser, id, key);
    parser.readNext();
    while (!parser.atEnd() && !parser.hasError() && _isValid && parser.tokenType() != QXmlStreamReader::EndElement){
        parser.readNext();
    }
    return;
}

void TestsetParser::parseTestData(QXmlStreamReader &parser, int id, int key) { //читает данные из тега data
    if (parser.tokenType() != QXmlStreamReader::StartElement || parser.name() != "data") {
        comment = "In test " + QString::number(id) + " Wrong tag:" + parser.name().toString() + " Expected data.";
        _isValid = false;
        return;
    }
    tests.resize(id);
    parser.readNext();
    while (!parser.atEnd() && _isValid && !parser.hasError() && parser.tokenType() != QXmlStreamReader::EndElement) {
        if (parser.tokenType() == QXmlStreamReader::StartElement)
        {
            QStringRef name = parser.name();
            parser.readNext();
            if (name == "AX" && isLabelNumberPointerReg->exactMatch(parser.text().toString())) {
                tests.back().insert("AX", encriptArg(parser.text().toString().toInt(), key));
                //qDebug() << "AX" << " " << encriptArg(hextoint(parser.text().toString()), key) << endl;
            }
            else if (name == "BX" && isLabelNumberPointerReg->exactMatch(parser.text().toString())) {
                tests.back().insert("BX", parser.text().toString().toInt());
                //qDebug() << "BX" << " " << encriptArg(hextoint(parser.text().toString()), key) << endl;
            }
            else if (name == "CX" && isLabelNumberPointerReg->exactMatch(parser.text().toString())) {
                tests.back().insert("CX", parser.text().toString().toInt());
                //qDebug() << "CX" << " " << encriptArg(hextoint(parser.text().toString()), key) << endl;
            }
            else if (name == "DX" && isLabelNumberPointerReg->exactMatch(parser.text().toString())) {
                tests.back().insert("DX", parser.text().toString().toInt());
                //qDebug() << "DX" << " " << encriptArg(hextoint(parser.text().toString()), key) << endl;
            }
            else if (name == "C" && isBit->exactMatch(parser.text().toString())) {
                tests.back().insert("C", parser.text().toString().toInt());
                //qDebug() << "C" << " " << encriptArg(hextoint(parser.text().toString()), key) << endl;
            }
            else if (name == "Z" && isBit->exactMatch(parser.text().toString())) {
                tests.back().insert("Z", parser.text().toString().toInt());
                //qDebug() << "Z" << " " << encriptArg(hextoint(parser.text().toString()), key) << endl;
            }
            else if (isTestMemoryContentReg->exactMatch(name.toString()) && isLabelNumberPointerReg->exactMatch(parser.text().toString())) {
                tests.back().insert(name.toString(), parser.text().toString().toInt());
                //qDebug() << name.toString() << " " << encriptArg(hextoint(parser.text().toString()), key) << endl;
            }
            else {
                comment = "In test " + QString::number(id) + ". Wrong parametr " + name.toString();
                _isValid = false;
                return;
            }
            parser.readNext();
        }
        parser.readNext();
    }
}

void TestsetParser::parseTestAnswer(QXmlStreamReader &parser, int id, int key = 0) {
    if (parser.tokenType() != QXmlStreamReader::StartElement || parser.name() != "answer") {
        comment = "In test " + QString::number(id) + " Wrong tag:" + parser.name().toString() + " Expected data.";
        _isValid = false;
        return;
    }
    answers.resize(id);
    parser.readNext();
    while (!parser.atEnd() && _isValid && !parser.hasError() && parser.tokenType() != QXmlStreamReader::EndElement) {
        if (parser.tokenType() == QXmlStreamReader::StartElement)
        {
            QStringRef name = parser.name();
            parser.readNext();
            if (name == "AX" && isLabelNumberPointerReg->exactMatch(parser.text().toString())) {
                answers.back().insert("AX", parser.text().toString().toInt());
                //qDebug() << "AX" << " " << encriptArg(hextoint(parser.text().toString()), key) << endl;
            }
            else if (name == "BX" && isLabelNumberPointerReg->exactMatch(parser.text().toString())) {
                answers.back().insert("BX", parser.text().toString().toInt());
                //qDebug() << "BX" << " " << encriptArg(hextoint(parser.text().toString()), key) << endl;
            }
            else if (name == "CX" && isLabelNumberPointerReg->exactMatch(parser.text().toString())) {
                answers.back().insert("CX", parser.text().toString().toInt());
                //qDebug() << "CX" << " " << encriptArg(hextoint(parser.text().toString()), key) << endl;
            }
            else if (name == "DX" && isLabelNumberPointerReg->exactMatch(parser.text().toString())) {
                answers.back().insert("DX", parser.text().toString().toInt());
                //qDebug() << "DX" << " " << encriptArg(hextoint(parser.text().toString()), key) << endl;
            }
            else if (name == "C" && isBit->exactMatch(parser.text().toString())) {
                answers.back().insert("C", parser.text().toString().toInt());
                //qDebug() << "C" << " " << encriptArg(hextoint(parser.text().toString()), key) << endl;
            }
            else if (name == "Z" && isBit->exactMatch(parser.text().toString())) {
                answers.back().insert("Z", parser.text().toString().toInt());
                //qDebug() << "Z" << " " << encriptArg(hextoint(parser.text().toString()), key) << endl;
            }
            else if (isTestMemoryContentReg->exactMatch(name.toString()) && isLabelNumberPointerReg->exactMatch(parser.text().toString())) {
                answers.back().insert(name.toString(), parser.text().toString().toInt());
                //qDebug() << name.toString() << " " << encriptArg(hextoint(parser.text().toString()), key) << endl;
            }
            else {
                comment = "In test " + QString::number(id) + ". Wrong parametr" + name.toString();
                _isValid = false;
                return;
            }
            parser.readNext();

        }
        parser.readNext();
    }
    encriptArg(0, key);
    return;
}

int TestsetParser::encriptArg(int val, int key = 0) {
    return (val ^ key);
}

QString TestsetParser::getComment() {
    return comment;
}

int TestsetParser::getTestCount() {
    return tests.size();
}

void TestsetParser::getTest(int id, QMap<QString, int> &test, QMap<QString, int> &answer) {
    test = tests[id];
    answer = answers[id];
    return;
}
