#include "about.h"
#include "ui_about.h"

About::About(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
  //  ui->label->setText("About");

}

About::~About()
{
    delete ui;
}
