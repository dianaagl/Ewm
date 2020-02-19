/********************************************************************************
** Form generated from reading UI file 'about.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUT_H
#define UI_ABOUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_About
{
public:
    QLabel *label;
    QTextBrowser *textBrowser;

    void setupUi(QWidget *About)
    {
        if (About->objectName().isEmpty())
            About->setObjectName(QStringLiteral("About"));
        About->resize(400, 300);
        label = new QLabel(About);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(0, 10, 401, 31));
        textBrowser = new QTextBrowser(About);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(35, 50, 341, 231));

        retranslateUi(About);

        QMetaObject::connectSlotsByName(About);
    } // setupUi

    void retranslateUi(QWidget *About)
    {
        About->setWindowTitle(QApplication::translate("About", "About", Q_NULLPTR));
        label->setText(QApplication::translate("About", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:16pt; color:#55007f;\">\320\255\320\222\320\234-\320\277\321\200\320\260\320\272\321\202\320\270\320\272\321\203\320\274. \320\222\320\265\321\200\321\201\320\270\321\217 1.2</span></p></body></html>", Q_NULLPTR));
        textBrowser->setHtml(QApplication::translate("About", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:7.875pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">\320\255\320\222\320\234-\320\277\321\200\320\260\320\272\321\202\320\270\320\272\321\203\320\274 - \321\215\321\202\320\276 \320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\274\320\275\320\260\321\217 \321\201\320\270\321\201\321\202\320\265\320\274\320\260, \320\262 \320\272\320\276\321\202\320\276\321\200\320\276\320\271\302\240 \320\262\302\240 \320\272\320\260\321\207\320\265\321\201\321\202\320\262\320\265 \320\276\320\261\321\212\320\265\320\272\321\202\320\276\320\262 \320\262\321\213\321\201\321\202\321"
                        "\203\320\277\320\260\321\216\321\202 \320\276\320\277\320\265\321\200\320\260\321\202\320\270\320\262\320\275\320\260\321\217\302\240 \320\277\320\260\320\274\321\217\321\202\321\214\302\240 \320\270 \321\200\320\265\320\263\320\270\321\201\321\202\321\200\321\213 \321\206\320\265\320\275\321\202\321\200\320\260\320\273\321\214\320\275\320\276\320\263\320\276 \320\277\321\200\320\276\321\206\320\265\321\201\321\201\320\276\321\200\320\260 \320\275\320\265\320\272\320\276\320\271 \320\262\320\270\321\200\321\202\321\203\320\260\320\273\321\214\320\275\320\276\320\271 \320\255\320\222\320\234.</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">\320\255\320\222\320\234-\320\277\321\200\320\260\320\272\321\202\320\270\320\272\321\203\320\274 \320\277\321\200\320\265\320\277\320\276\320\264\320\260\320\265\321\202\321\201\321\217 \320\275\320\260 \320\274\320\265\321\205\320\260\320\275\320\270\320"
                        "\272\320\276-\320\274\320\260\321\202\320\265\320\274\320\260\321\202\320\270\321\207\320\265\321\201\320\272\320\276\320\274 \321\204\320\260\320\272\321\203\320\273\321\214\321\202\320\265\321\202\320\265 \320\234\320\223\320\243 \320\270\320\274.\320\234.\320\222.\320\233\320\276\320\274\320\276\320\275\320\276\321\201\320\276\320\262\320\260 \320\270 \321\200\320\260\321\201\320\277\321\200\320\276\321\201\321\202\321\200\320\260\320\275\320\260\320\265\321\202\321\201\321\217 \321\201\320\262\320\276\320\261\320\276\320\264\320\275\320\276 \320\275\320\260 \321\203\321\201\320\273\320\276\320\262\320\270\321\217\321\205 \320\273\320\270\321\206\320\265\320\275\320\267\320\270\320\270 GNU GPL v.2.</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">\320\233\321\216\320\261\321\213\320\265 \320\262\320\276\320\277\321\200\320\276\321\201\321\213 \320\277\320\276 \320\270\321\201\320\277\320\276"
                        "\320\273\321\214\320\267\320\276\320\262\320\260\320\275\320\270\321\216 \320\255\320\222\320\234-\320\277\321\200\320\260\320\272\321\202\320\270\320\272\321\203\320\274\320\260 \320\275\320\260\320\277\321\200\320\260\320\262\320\273\321\217\320\271\321\202\320\265 \321\200\321\203\320\272\320\276\320\262\320\276\320\264\320\270\321\202\320\265\320\273\321\216 \320\277\321\200\320\276\320\265\320\272\321\202\320\260 \320\233\320\265\320\276\320\275\320\276\320\262\321\203 \320\220.\320\223.</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">e-mail: </span><span style=\" font-size:8pt; font-weight:600;\">dr.l@math.msu.su</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">\320\241\320\260\320\271\321\202 \321\200\320\260\320\267\321\200\320\260\320\261\320\276\321\202\320\272\320"
                        "\270: </span><span style=\" font-size:8pt; font-weight:600;\">http://e.kumir.su</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt; font-weight:600;\">(C) \320\230\320\275\321\204\320\276\320\234\320\270\321\200 2012-2017</span></p></body></html>", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class About: public Ui_About {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUT_H
