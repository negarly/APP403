#include "signup.h"
#include "ui_signup.h"
#include"topicwindow.h"
#include<QString>
#include<QElapsedTimer>

signup::signup(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::signup)
    // ,_topicwindow(_topicwindow)
{
    socket = new QTcpSocket(this);

    ui->setupUi(this);
    connect(socket, &QTcpSocket::connected, this, &signup::socket_connected);
    connect(socket, &QTcpSocket::disconnected, this, &signup::socket_disconnected);
    connect(socket, &QTcpSocket::readyRead, this, &signup::readSocketData);
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(socket_error(QAbstractSocket::SocketError)));

}

void signup::showEvent(QShowEvent *event) {
    QMainWindow::showEvent(event);
    socket->connectToHost("localhost", 1234);
    if (!socket->waitForConnected(2000)) {
        qDebug() << "Error: " << socket->errorString();
    }
}

void signup::closeEvent(QCloseEvent *event) {
    socket->close();
    qDebug()<<"socket closed";

    QMainWindow::closeEvent(event);

}
signup::~signup()
{
    delete ui;
}

void signup::socket_disconnected()
{
    qDebug() << "Disconnected from the server!";
}


void signup::on_signupButton_clicked()
{
    setCursor(Qt::WaitCursor);
    if (!socket->waitForConnected(2000)) {
        qDebug() << "Error: " << socket->errorString();
        return;
    }

    if (socket->state() != QTcpSocket::ConnectedState) {
        qDebug() << "Error in connection";
        return;
    }
    QString username = ui->useredit->text();
    QString password = ui->passedit->text();
    QString email = ui->eedit->text();

    QJsonObject json;
    json["command"] = "signup";

    json["username"] = username;
    json["password"] = password;
    json["email"] = email;

    QJsonDocument jsonDoc(json);
    QByteArray jsonData = jsonDoc.toJson();

    socket->write(jsonData);
    qDebug()<<jsonData;

    topicwindow *_topicwindow = new topicwindow(username, email, this);
    _topicwindow->show();
    this->hide();
}


void signup::socket_connected()
{
    qDebug() << "Connected to server";
}

void signup::readSocketData()
{
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
    if (!socket) return;


    QByteArray responseData = socket->readAll();
    QString response = QString::fromUtf8(responseData);
    qDebug() << "Received response from server:" << response;

    // QByteArray buffer;
    // // QDataStream in(socket);
    // // in.setVersion(QDataStream::Qt_5_0);

    // // while(!in.atEnd()){
    // //     buffer.append(socket->readAll());
    // //     qDebug() << buffer;
    // //     if (socket->waitForReadyRead(5000)) continue;
    // // }

    // // if (buffer.isEmpty()) {
    // //     qDebug() << "No data received or connection closed.";
    // //     return;
    // // }


    // // QJsonDocument jsonDoc = QJsonDocument::fromJson(buffer);
    // // if (jsonDoc.isNull()) {
    // //     qDebug() << "Failed to parse JSON.";
    // //     return;
    // // }
    // QElapsedTimer timer;
    // timer.start();

    // while (socket->bytesAvailable() > 0 || socket->waitForReadyRead(500)) {
    //     buffer.append(socket->readAll());
    //     if (timer.elapsed() >= 500) {
    //         unsetCursor();
    //         break;
    //     }
    // }

    // if (buffer.isEmpty()) {
    //     qDebug() << "No data received or connection closed.";
    //     return;
    // }

    // QJsonParseError parseError;
    // QJsonDocument jsonDoc = QJsonDocument::fromJson(buffer, &parseError);

    // if (jsonDoc.isNull()) {
    //     qDebug() << "Failed to parse JSON:" << parseError.errorString();
    //     qDebug() << "Received data:" << buffer;
    //     return;
    // }

    // // Process the JSON document
    // qDebug() << "JSON document successfully parsed:" << jsonDoc.toJson(QJsonDocument::Indented);
    // QJsonArray jsonArray = jsonDoc.array();

    // qDebug() << "Users:" << jsonArray;


}

void signup::socket_error(QAbstractSocket::SocketError error )
{
    qDebug() << "Socket error: " << socket->errorString();
}
