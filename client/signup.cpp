#include "signup.h"
#include "ui_signup.h"
#include"topicwindow.h"
#include<QString>

signup::signup(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::signup)
    , socket(new QTcpSocket(this))
    // ,_topicwindow(_topicwindow)
{
    ui->setupUi(this);
    connect(socket, &QTcpSocket::connected, this, &signup::onConnected);
    connect(socket, &QTcpSocket::readyRead, this, &signup::onReadyRead);
}

signup::~signup()
{
    delete ui;
}

void signup::on_signupButton_clicked()
{
    QString username = ui->useredit->text();
    QString password = ui->passedit->text();
    QString email = ui->eedit->text();

    QJsonObject json;
    json["username"] = username;
    json["password"] = password;
    json["email"] = email;

    QJsonDocument jsonDoc(json);
    QByteArray jsonData = jsonDoc.toJson();

    socket->connectToHost("localhost", 8080);
    if (socket->waitForConnected(5000)) {
        socket->write(jsonData);
    }
    topicwindow *_topicwindow = new topicwindow(username, email, this);
    _topicwindow->show();
    this->hide();
}


void signup::onConnected()
{
    qDebug() << "Connected to server";
}

void signup::onReadyRead()
{
    QByteArray responseData = socket->readAll();

    qDebug() << "Server response:" << responseData;


}
