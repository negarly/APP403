#include "topicwindow.h"
#include "ui_topicwindow.h"
#include"gamewindow.h"
#include"signup.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QFile>
#include<QDialog>
#include<QTimer>
#include<QElapsedTimer>

topicwindow::topicwindow(const QString &username, const QString &email,QWidget *parent)
    :QMainWindow(parent)
    , ui(new Ui::topicwindow)
, socket(nullptr)
    // , waitingBox(new QMessageBox(this))

{
    socket = new QTcpSocket(this);

    ui->setupUi(this);
    connect(socket, &QTcpSocket::readyRead, this, &topicwindow::on_pushButton_clicked);
    connect(socket, &QTcpSocket::connected, this, &topicwindow::socket_connected);
    connect(socket, &QTcpSocket::disconnected, this, &topicwindow::socket_disconnected);
    connect(socket, &QTcpSocket::readyRead, this, &topicwindow::readSocketData);
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(socket_error(QAbstractSocket::SocketError)));

    ui->usernamelabel->setText("Username: " + username);
    ui->emaillabel->setText("email: " + email);
}

void topicwindow::showEvent(QShowEvent *event) {
    QMainWindow::showEvent(event);
    socket->connectToHost("localhost", 1234);
    if (!socket->waitForConnected(2000)) {
        qDebug() << "Error: " << socket->errorString();
    }
}

void topicwindow::closeEvent(QCloseEvent *event) {
    socket->close();
    qDebug()<<"socket closed";

    QMainWindow::closeEvent(event);

}

topicwindow::~topicwindow()
{
    delete ui;
}

void topicwindow::socket_connected()
{
    qDebug() << "Connected to the server!";
}

void topicwindow::socket_disconnected()
{
    qDebug() << "Disconnected from the server!";
}

void topicwindow::readSocketData()
{

    if (!socket) return;


    QByteArray responseData = socket->readAll();
    QString response = QString::fromUtf8(responseData);
    qDebug() << "Received response from server:" << response;
    if (response.contains("WAIT_FOR_PLAYER"))
    {
        QMessageBox::information(nullptr, "Waiting", "Waiting for another player...");
    }
    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData, &parseError);
    if (jsonDoc.isNull()) {
        qDebug() << "Failed to parse JSON response:" << parseError.errorString();
        return;
    }
    QJsonObject rootObj = jsonDoc.object();
    if(rootObj["command"] == "start_game"){
        if(rootObj["message"] == "WAIT_FOR_PLAYER"){
            QMessageBox::critical(this, "waiting", "wait for another player.");

        }
        else if(rootObj["message"] == "GAME_STILL_ON"){
            QMessageBox::critical(this, "waiting", "a game still on.");

        }
        if(rootObj["message"] == "START_GAME_PAGE"){
            gamewindow *_gamewindow = new gamewindow(this);
            _gamewindow->show();
            this->hide();

        }
    }
    // QByteArray buffer;
    // // QDataStream in(socket);
    // // in.setVersion(QDataStream::Qt_5_0);

    // QElapsedTimer timer;
    // timer.start();

    // // while(!in.atEnd()){
    // //     buffer.append(socket->readAll());
    // //     if (socket->waitForReadyRead(500)) continue;
    // //     else{
    // //         if (timer.elapsed() >= 500) {
    // //             unsetCursor();
    // //         }
    // //     }
    // //     unsetCursor();
    // // }
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

    // // QJsonDocument jsonDoc = QJsonDocument::fromJson(buffer);
    // // if (jsonDoc.isNull()) {
    // //     qDebug() << "Failed to parse JSON.";
    // //     return;
    // // }
    // QJsonParseError parseError;
    // QJsonDocument jsonDoc = QJsonDocument::fromJson(buffer, &parseError);

    // if (jsonDoc.isNull()) {
    //     qDebug() << "Failed to parse JSON" << parseError.errorString();
    //     qDebug() << "Offset:" << parseError.offset;

    //     qDebug() << "Received data:" << buffer;
    //     return;
    // }
    // QJsonObject responseObj = jsonDoc.object();
    // qDebug() << responseObj;

}

void topicwindow::socket_error(QAbstractSocket::SocketError error )
{
    qDebug() << "Socket error: " << socket->errorString();
}
void topicwindow::on_pushButton_clicked()
{
    QJsonObject json;
    json["command"] = "start_game";

    QJsonDocument jsonDoc(json);
    QByteArray jsonData = jsonDoc.toJson();

    socket->write(jsonData);
    gamewindow *_gamewindow = new gamewindow(this);
    _gamewindow->show();
    this->hide();
}
