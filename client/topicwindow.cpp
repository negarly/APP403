#include "topicwindow.h"
#include "ui_topicwindow.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QFile>
#include<QDialog>

topicwindow::topicwindow(const QString &username, const QString &email,QWidget *parent)
    :QMainWindow(parent)
    , ui(new Ui::topicwindow)

{
    ui->setupUi(this);
    ui->usernamelabel->setText("Username: " + username);
    ui->emaillabel->setText("email: " + email);
}

topicwindow::~topicwindow()
{
    delete ui;
}
