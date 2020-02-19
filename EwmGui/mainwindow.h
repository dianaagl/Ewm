#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QListWidget>
#include <QMainWindow>

#include "codeeditor.h"


#include "functions.h"

#include "testsetparser.h"
#include <QMenu>
#include <QMenuBar>
#include "ewmtesting.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QRegExp *isSpaceReg, *isMemoryContentReg, *isTestMemoryContentReg, *isArrayPointerReg;
    QRegExp *isLabelNumberPointerReg;
    QRegExp *isLabelWordReg, *isLabelWordPointerReg;

    QRegExp* binRegExp = new QRegExp("^[0-1]{0,16}$");
    QRegExp* hexRegExp = new QRegExp("^[0-9A-Fa-f]{0,4}$");
    QRegExp* decRegExp = new QRegExp("^[0-9]{0,5}$");
    QRegExp* boolRegExp = new QRegExp("^[0-1]{0,1}$");

    QRegExpValidator* binRegValidator = new QRegExpValidator(*binRegExp, 0);
    QRegExpValidator* hexRegValidator = new QRegExpValidator(*hexRegExp, 0);
    QRegExpValidator* decRegValidator = new QRegExpValidator(*decRegExp, 0);
    QRegExpValidator* boolRegValidator = new QRegExpValidator(*boolRegExp, 0);


    EwmTesting * ewmPrac;
    AllMemory * allMemory;

    CodeEditor *codeeditor;


    QListWidget *errorWindow;
    

    QString testText, testPath;
    void initMemory(QMap<QString, int> *test);
    bool isCorrect(QMap<QString, int> *answer);

    int startTime;
    
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void compile();
    bool makeStep();
    bool makeStepUpdate();
    Memory *get_operand(int);
    void createMemoryTable(int n, int m);
    void createStack();
    void updateRegisters();
    void updateMemoryTable();
    void saveMemoryTable();

public slots:
    void updateMemoryCell();
    void on_compileButton_clicked();
    void on_stepButton_clicked();
    void on_runButton_clicked();
    void on_stopButton_clicked();

    void on_NewButton_clicked();
    void on_OpenButton_clicked();
    void on_SaveButton_clicked();
    void on_SaveAsButton_clicked();
    
    void on_downloadTestsetButton_clicked();
    void on_startTestingButton_clicked();
    void on_aboutButton_clicked();


    void key_get();
    void key_update();

    void on_binRadioButton_clicked();
    void on_decRadioButton_clicked();
    void on_hexRadioButton_clicked();


signals:
    void key_changed();

private slots:
    void on_binTableRadioButton_clicked();

    void on_dexTableRadioButton_clicked();

    void on_hexTableRadioButton_clicked();

    void on_memoryTableWidget_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);


private:
    Ui::MainWindow *ui;

};



#endif // MAINWINDOW_H

