#include "about.h"
#include "ui_about.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include <QHBoxLayout>
#include <QPushButton>
#include <iostream>
#include <QFileDialog>

#define BEGIN_CONST 48
#define END_CONST 49
#define DOT_CONST 50
#define LABEL_NUMBER_POINTER 52
#define LABEL_WORD 52
#define LABEL_WORD_POINTER 53
#define TIME_LIMIT 1

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle ( tr("E-praktikum"));

    ewmPrac = new EwmTesting();

    allMemory = ewmPrac->getMemoryTable(2);


    testText = "";
    testPath = QDir::homePath();




    createMemoryTable(64,8);
    createStack();
    errorWindow = ui->errorWindow;
    codeeditor = ui->codeEditor;

/*----------------------QRegExp------------------------*/
    isSpaceReg = new QRegExp("\\s");
    isMemoryContentReg = new QRegExp("^\\[[0-9A-F]{1,4}\\]$");
    isArrayPointerReg = new QRegExp("^[0-9A-F]{1,4}\\([A-D]{1,1}X\\)$");
    isLabelNumberPointerReg = new QRegExp("^[0-9A-F]{1,4}$");
    isTestMemoryContentReg = new QRegExp("^Mem([0-9]{1,5})$");
    isLabelWordPointerReg = new QRegExp("^\\?[0-9A-F]{1,4}$");
    isLabelWordReg = new QRegExp("^\\?[0-9A-F]{1,4}\\:$");

/*----------------------- VIEW ------------------------*/

   ui->AxLineEdit->setMinimumWidth(2 + fontMetrics().width(QLatin1Char('9')) * 16);
   ui->BxLineEdit->setMinimumWidth(2 + fontMetrics().width(QLatin1Char('9')) * 16);
   ui->CxLineEdit->setMinimumWidth(2 + fontMetrics().width(QLatin1Char('9')) * 16);
   ui->DxLineEdit->setMinimumWidth(2 + fontMetrics().width(QLatin1Char('9')) * 16);

    ui->AxLineEdit->setMaximumWidth(2 + fontMetrics().width(QLatin1Char('9')) * 16);
    ui->BxLineEdit->setMaximumWidth(2 + fontMetrics().width(QLatin1Char('9')) * 16);
    ui->CxLineEdit->setMaximumWidth(2 + fontMetrics().width(QLatin1Char('9')) * 16);
    ui->DxLineEdit->setMaximumWidth(2 + fontMetrics().width(QLatin1Char('9')) * 16);

    codeeditor->setFocus();

 }

void MainWindow::createMemoryTable(int n, int m)
{
    QTableWidget* memoryTable = ui->memoryTableWidget;
    memoryTable->setRowCount(n);
    memoryTable->setColumnCount(m);

    for (int i = 0; i < n*m; i++)
    {
        QLineEdit * lineEdit = new QLineEdit();
        connect(lineEdit, SIGNAL(editingFinished()), this, SLOT(updateMemoryCell()));

        memoryTable->setCellWidget(i/m, i%m, lineEdit);
    }

/* VERTICAL AND HORIZONTAL ITEMS OF TABLE */
    for (int i = 0; i < n; i++)
    {
        QTableWidgetItem *item = new QTableWidgetItem;
        item->setText(inttohex(i*8));
        ui->memoryTableWidget->setVerticalHeaderItem(i, item);
    }

    for (int i = 0; i < m; i++)
    {
        QTableWidgetItem *item = new QTableWidgetItem;
//        item->setText(inttohex(i));
        item->setText(inttostr(i));
        ui->memoryTableWidget->setHorizontalHeaderItem(i, item);
        ui->memoryTableWidget->setColumnWidth(i, 4 + fontMetrics().width(QLatin1Char('9')) * 5);
    }

    /* --------------------------------------------------------------*/

    ui->hexTableRadioButton->click();
    ui->hexRadioButton->click();

    /* ----------------------------- VIEW --------------------------- */

//    ui->memoryTableWidget->setMinimumWidth((5 + fontMetrics().width(QLatin1Char('9')) * 5) * 9 + 4);
//    ui->memoryTableWidget->setMaximumWidth((5 + fontMetrics().width(QLatin1Char('9')) * 5) * 9 + 4);
//    ui->memoryTableWidget->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
}

void MainWindow::createStack()
{

    ui->stackWidget->addItems(allMemory->stack.toList());

}

void MainWindow::on_NewButton_clicked(){
    testPath = QDir::homePath();
    codeeditor->setPlainText("");
}

void MainWindow::on_OpenButton_clicked(){

    QString file_path =  QDir::homePath();
    file_path = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                               file_path,
                                                               tr("Text files (*.txt)"));

    ewmPrac->setProgramCode(file_path);


    codeeditor->setPlainText(ewmPrac->getProgramCode());
    errorWindow->addItems(*ewmPrac->prog->errorWindow);
    compile();
}

void MainWindow::on_SaveButton_clicked(){
   ewmPrac->saveProgram(codeeditor->toPlainText());
}


void MainWindow::on_SaveAsButton_clicked()
{

    QString FilePath = QFileDialog::getSaveFileName(this, tr("Save File As"),
                                            QDir::homePath(),
                                            tr("Text files (*.txt)"));
   ewmPrac->testPath = FilePath;
   ewmPrac->saveProgram(codeeditor->toPlainText());
}

MainWindow::~MainWindow()
{

}

bool MainWindow::makeStepUpdate()
{
    qDebug() <<  "equal " << ewmPrac->prog->getCodeText().compare(codeeditor->toPlainText());
    if(ewmPrac->prog->getCodeText().compare(codeeditor->toPlainText()) != 0)
    {
        on_stopButton_clicked();
        compile();
        return false;
    }
    bool res = makeStep();
    updateRegisters();
    updateMemoryTable();
    ui->stackWidget->clear();
    ui->stackWidget->addItems(allMemory->stack.toList());
    ui->stackWidget->update();

    return res;

}

bool MainWindow::makeStep()
{

    if(!ewmPrac->makeStep())
    {
        codeeditor->moveCursor(QTextCursor::Start);

        if (!ewmPrac->prog->isCompiled())
        {
            return false;
        }
    }
    codeeditor->moveCursor(QTextCursor::Start);
    for (int i = 1; i < ewmPrac->prog->currLine; i++)
        codeeditor->moveCursor(QTextCursor::Down);
    errorWindow->clear();
    errorWindow->addItems(*ewmPrac->prog->errorWindow);
    return true;

}

void MainWindow::compile()
{
    qDebug() <<"compile mainWindow";
    errorWindow->clear();
    ewmPrac->prog->setCodeText(codeeditor->toPlainText());
    ewmPrac->prog->compile();
    codeeditor->setPlainText(ewmPrac->getProgramCode());
    errorWindow->addItems(*ewmPrac->prog->errorWindow);
    saveMemoryTable();

}

void MainWindow::on_compileButton_clicked()
{
    MainWindow::compile();
}

void MainWindow::on_stepButton_clicked()
{
    MainWindow::makeStepUpdate();
}

void MainWindow::on_runButton_clicked()
{
    compile();
    errorWindow->clear();
    if (!ewmPrac->prog->isCompiled())
    {
        errorWindow->insertItem(0, tr("Some errors in project:"));
        return;
    }

    startTime = ewmPrac->timer.elapsed();
    qDebug() << "startTime" << startTime;
    while (ewmPrac->prog-> currLine < ewmPrac->prog->lineCount-1)
    {
        this->makeStepUpdate();
        if ((ewmPrac->timer.elapsed() -startTime)/1000 > TIME_LIMIT)
        {
            errorWindow->addItem(tr("Project stoped due to time-limit;"));
            break;
        }
            qDebug() << "curTime" << (ewmPrac->timer.elapsed()-startTime)/1000;
    }
    codeeditor->moveCursor(QTextCursor::Down);

    errorWindow->addItems(*ewmPrac->prog->errorWindow);
}

void MainWindow::on_stopButton_clicked()
{
    ewmPrac->prog->currLine = 1;
    codeeditor->moveCursor(QTextCursor::Start);
    allMemory->stack.clear();
    ui->stackWidget->clear();
}

void MainWindow::initMemory(QMap<QString, int>  *test = NULL) {
    ewmPrac->initMemory();
//                allmemory->memory[index].set_key(it.value());
 //               ((QLineEdit) ui->memoryTableWidget->cellWidget(index/allmemory->m, index%allmemory->m)).setText(allmemory->memory[index].getVal());


    return;
}


void MainWindow::on_startTestingButton_clicked()
{
    ewmPrac->startTesting();
    errorWindow->clear();
    errorWindow->addItems(*ewmPrac->prog->errorWindow);

    updateRegisters();
    saveMemoryTable();
}

void MainWindow::on_aboutButton_clicked()
{
    About *About_out  = new About();
    About_out->show();
}


void MainWindow::on_downloadTestsetButton_clicked()
{
    QString tmpTestPath = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                       testPath,
                                                       tr("Testset files (*.testset)"));
    errorWindow->clear();
    ewmPrac->downloadTestset(tmpTestPath);
    updateRegisters();
    updateMemoryTable();
    errorWindow->addItems(*ewmPrac->prog->errorWindow);
}






void MainWindow::on_binRadioButton_clicked()
{
    allMemory->toConditionReg(0);
    std::vector<QLineEdit*> edits ={ui->AxLineEdit,ui->BxLineEdit,ui->CxLineEdit,ui->DxLineEdit};

    for(int i = 0;i < edits.size();i++){
        edits[i]->setValidator(binRegValidator);
        edits[i]->setText(allMemory->reg[i]->getVal());
    }
}

void MainWindow::on_decRadioButton_clicked()
{
    allMemory->toConditionReg(1);
    std::vector<QLineEdit*> edits ={ui->AxLineEdit,ui->BxLineEdit,ui->CxLineEdit,ui->DxLineEdit};

    for(int i = 0;i < (int)edits.size();i++){
        edits[i]->setValidator(decRegValidator);
        edits[i]->setText(allMemory->reg[i]->getVal());
    }
}

void MainWindow::on_hexRadioButton_clicked()
{
     qDebug() << "hex button clicked";
    std::vector<QLineEdit*> edits ={ui->AxLineEdit,ui->BxLineEdit,ui->CxLineEdit,ui->DxLineEdit};
//     for(int i = 0;i < edits.size();i++){
//        allMemory->reg[i]->setVal(QString(edits[i]->text()));
//        qDebug() << edits[i]->text() << allMemory->reg[i]->getVal();
//     }
    allMemory->toConditionReg(2);

    for(int i = 0;i < edits.size();i++){
            qDebug() << "mem" << allMemory->reg[i]->getVal();
        edits[i]->setValidator(hexRegValidator);

        edits[i]->setText(allMemory->reg[i]->getVal());
    }
}

void MainWindow::key_get()
{
    QObject* obj = sender();

        qDebug() << "key get";
      if( obj == ui->AxLineEdit )
      {
          allMemory->reg[0]->setVal(QString(ui->AxLineEdit->text()));
          allMemory->reg[0]->key_get();
          ui->AxLineEdit->setText(allMemory->reg[0]->getVal());
          qDebug() << allMemory->reg[0]->getVal();
      }
      if(obj == ui->BxLineEdit)
      {
          allMemory->reg[1]->setVal(QString(ui->BxLineEdit->text()));
          allMemory->reg[1]->key_get();
          ui->BxLineEdit->setText(allMemory->reg[1]->getVal());


      }
      if(obj == ui->CxLineEdit)
      {
          allMemory->reg[2]->setVal(QString(ui->CxLineEdit->text()));
          allMemory->reg[2]->key_get();
          ui->CxLineEdit->setText(allMemory->reg[2]->getVal());


      }
      if(obj == ui->DxLineEdit)
      {
          allMemory->reg[3]->setVal(QString(ui->DxLineEdit->text()));
          allMemory->reg[3]->key_get();
          ui->DxLineEdit->setText(allMemory->reg[3]->getVal());


      }
      if(obj == ui->CEditLine)
      {
          allMemory->reg[4]->setVal(QString(ui->CEditLine->text()));
          allMemory->reg[4]->key_get();
          ui->CEditLine->setText(allMemory->reg[4]->getVal());


      }
      if(obj == ui->ZEditLine)
      {
          allMemory->reg[5]->setVal(QString(ui->ZEditLine->text()));
          allMemory->reg[5]->key_get();
          ui->ZEditLine->setText(allMemory->reg[5]->getVal());


      }
      else
      {
          allMemory->reg[0]->setVal(QString(ui->AxLineEdit->text()));
          allMemory->reg[0]->key_get();
          ui->AxLineEdit->setText(allMemory->reg[0]->getVal());
          qDebug() << allMemory->reg[0]->getVal();

          allMemory->reg[1]->setVal(QString(ui->BxLineEdit->text()));
          allMemory->reg[1]->key_get();
          ui->BxLineEdit->setText(allMemory->reg[1]->getVal());

          allMemory->reg[2]->setVal(QString(ui->CxLineEdit->text()));
          allMemory->reg[2]->key_get();
          ui->CxLineEdit->setText(allMemory->reg[2]->getVal());

          allMemory->reg[3]->setVal(QString(ui->DxLineEdit->text()));
          allMemory->reg[3]->key_get();
          ui->DxLineEdit->setText(allMemory->reg[3]->getVal());

          allMemory->reg[4]->setVal(QString(ui->CEditLine->text()));
          allMemory->reg[4]->key_get();
          ui->CEditLine->setText(allMemory->reg[4]->getVal());

          allMemory->reg[5]->setVal(QString(ui->ZEditLine->text()));
          allMemory->reg[5]->key_get();
          ui->ZEditLine->setText(allMemory->reg[5]->getVal());
      }
}
void MainWindow::key_update()
{
    std::vector<QLineEdit*> edits ={ui->AxLineEdit,ui->BxLineEdit,ui->CxLineEdit,ui->DxLineEdit};
    allMemory->key_update();
}

void MainWindow::on_binTableRadioButton_clicked()
{
    QLineEdit* cell;
    int n = allMemory->n;
    int m = allMemory->m;
    for(int i = 0;i < n;i++){
        for(int j = 0;j < m;j++){
            cell = (QLineEdit*)ui->memoryTableWidget->cellWidget(i,j);
            allMemory->memory[i*m +j].setVal(cell->text());
            allMemory->memory[i*m +j].key_get();
            cell->setValidator(binRegValidator);
            allMemory->memory[i*m +j].to_bin();
            cell->setText(allMemory->memory[i*m +j].getVal());
        }
    }

    for(int i = 0;i < m;i++){
        ui->memoryTableWidget->setColumnWidth(i, fontMetrics().width(QLatin1Char('0')) * 16);
    }

    //ui->memoryTableWidget->setMaximumWidth(fontMetrics().width(QLatin1Char('0')) * (19*m + 4));
//    ui->memoryTableWidget->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    //setMaximumWidth(ui->memoryTableWidget->width() + ui->codeEditor->width() + ui->box->width());


}


void MainWindow::on_dexTableRadioButton_clicked()
{
    QLineEdit* cell;
    int n = allMemory->n;
    int m = allMemory->m;
    for(int i = 0;i < n;i++){
        for(int j = 0;j < m;j++){
            cell = (QLineEdit*)ui->memoryTableWidget->cellWidget(i,j);
            allMemory->memory[i*m +j].setVal(cell->text());
            allMemory->memory[i*m +j].key_get();
            cell->setValidator(decRegValidator);
            allMemory->memory[i*m +j].to_dec();
            cell->setText(allMemory->memory[i*m +j].getVal());
        }
    }
    for(int i = 0;i < m;i++){
        ui->memoryTableWidget->setColumnWidth(i, fontMetrics().width(QLatin1Char('0')) *11);
    }

    resize(fontMetrics().width(QLatin1Char('0')) *11 + ui->codeEditor->width() + ui->box->width(), height());

//    int maxWidth = fontMetrics().width(QLatin1Char('0')) * (11*m + 4);
//     //ui->memoryTableWidget->setMaximumWidth(maxWidth);
//     ui->memoryTableWidget->resize(maxWidth, ui->memoryTableWidget->height());
//     resize(maxWidth + ui->codeEditor->width() + ui->box->width(), height());


}

void MainWindow::on_hexTableRadioButton_clicked()
{
    QLineEdit* cell;
    int n = allMemory->n;
    int m = allMemory->m;
    for(int i = 0;i < n;i++){
        for(int j = 0;j < m;j++){
            cell = (QLineEdit*)ui->memoryTableWidget->cellWidget(i,j);
            allMemory->memory[i*m +j].setVal(cell->text());
            allMemory->memory[i*m +j].key_get();
            cell->setValidator(hexRegValidator);
            allMemory->memory[i*m +j].to_hex();
            cell->setText(allMemory->memory[i*m +j].getVal());
        }
    }
    for(int i = 0;i < m;i++){
        ui->memoryTableWidget->setColumnWidth(i, fontMetrics().width(QLatin1Char('0')) * 5);
    }

        resize(fontMetrics().width(QLatin1Char('0')) * (5*m) + ui->codeEditor->width() + ui->box->width(), height());
//      ui->memoryTableWidget->setMinimumWidth(fontMetrics().width(QLatin1Char('0')) * (7*m) + 30);
//      //setMaximumWidth(ui->memoryTableWidget->width() + ui->codeEditor->width() + ui->box->width());

}
void MainWindow::updateRegisters()
{
    allMemory->key_update();
    ui->AxLineEdit->setText(allMemory->reg[0]->getVal());
    ui->BxLineEdit->setText(allMemory->reg[1]->getVal());
    ui->CxLineEdit->setText(allMemory->reg[2]->getVal());
    ui->DxLineEdit->setText(allMemory->reg[3]->getVal());

    ui->CEditLine->setText(allMemory->reg[4]->getVal());
    ui->ZEditLine->setText(allMemory->reg[5]->getVal());

}
void MainWindow::updateMemoryTable()
{
    int n = allMemory->n, m = allMemory->m;
    for (int i = 0; i < n; i++)
    {
        for(int j = 0;j < m; j++){
            QLineEdit* item2 = (QLineEdit*)ui->memoryTableWidget->cellWidget(i ,j);

            int cond = allMemory->memory[i*m + j].cond;
            if (cond == 0)
                item2->setValidator(binRegValidator);
            else if (cond == 1)
                item2->setValidator(decRegValidator);
            else if (cond == 2)
                item2->setValidator(hexRegValidator);

            item2->setText(allMemory->memory[i*m +j].getVal());
        }
    }
}

void MainWindow::saveMemoryTable()
{
    int n = allMemory->n, m = allMemory->m;
    for (int i = 0; i < n; i++)
    {
        for(int j = 0;j < m; j++){
            QLineEdit* item2 = (QLineEdit*)ui->memoryTableWidget->cellWidget(i ,j);

            int cond = allMemory->memory[i*m + j].cond;
            if (cond == 0)
                item2->setValidator(binRegValidator);
            else if (cond == 1)
                item2->setValidator(decRegValidator);
            else if (cond == 2)
                item2->setValidator(hexRegValidator);

            allMemory->memory[i*m +j].setVal(item2->text());
            allMemory->memory[i*m +j].key_get();
            item2->setText(allMemory->memory[i*m +j].getVal());

        }
    }
}

void MainWindow::updateMemoryCell()
{
    QLineEdit* obj = (QLineEdit*)sender();
    int n = allMemory->n, m = allMemory->m;
    int row = ui->memoryTableWidget->currentRow();
    int column = ui->memoryTableWidget->currentColumn();

    int cond = allMemory->memory[row*m + column].cond;
    if (cond == 0)
        obj->setValidator(binRegValidator);
    else if (cond == 1)
        obj->setValidator(decRegValidator);
    else if (cond == 2)
        obj->setValidator(hexRegValidator);

    allMemory->memory[ row*m + column].setVal(obj->text());
    allMemory->memory[ row*m + column].key_get();
    obj->setText(allMemory->memory[row*m + column].getVal());
}

void MainWindow::on_memoryTableWidget_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    int n = allMemory->n, m = allMemory->m;
    if(previousRow >=0 && previousColumn >= 0)
    {
        QLineEdit* item2 = (QLineEdit*)ui->memoryTableWidget->cellWidget(previousRow ,previousColumn);

        allMemory->memory[previousRow*m + previousColumn].setVal(item2->text());
        allMemory->memory[previousRow*m + previousColumn].key_get();

        int cond = allMemory->memory[previousRow*m + previousColumn].cond;
        if (cond == 0)
            item2->setValidator(binRegValidator);
        else if (cond == 1)
            item2->setValidator(decRegValidator);
        else if (cond == 2)
            item2->setValidator(hexRegValidator);

        item2->setText(allMemory->memory[previousRow*m +previousColumn].getVal());

        qDebug() << item2->text();
    }
//qDebug() <<  item->
    ;
}


