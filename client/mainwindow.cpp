#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"signup.h"


MainWindow::MainWindow(QWidget *parent,signup *_signup)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,_signup(_signup)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_signup_clicked()
{

    this->hide();
    _signup->show();

}

