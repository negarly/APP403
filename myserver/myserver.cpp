#include "myserver.h"
// #include "ui_mainwindow.h"

#include <QCryptographicHash>


myserver::myserver(QWidget *parent)
    : QTcpServer(parent)
  /*  , ui(new Ui::MainWindow)*/
{
    // ui->setupUi(this);

    if (!listen(QHostAddress::Any, 8080)) {
        qDebug() << "Server could not start!";
    } else {
        qDebug() << "Server started on port" << serverAddress().toString() << ":" << serverPort();
    }

    userfile = new QFile("users.txt");
    // gamestatsfile = new QFile("game_stats.txt");
    if (!userfile->open(QIODevice::Append | QIODevice::Text)) {
        qDebug() << "Unable to open user file";
    }/*
    if (!gamestatsfile->open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug() << "Unable to open game stats file";
    }*/
}

myserver::~myserver()
{
    // delete ui;

}


void myserver::incomingConnection(qintptr socketDescriptor)
{
    QTcpSocket *socket = new QTcpSocket(this);
    socket->setSocketDescriptor(socketDescriptor);

    connect(socket, &QTcpSocket::readyRead, this, &myserver::handleRequest);
    connect(socket, &QTcpSocket::disconnected, this, &myserver::disconnected);

    qDebug() << "New connection from" << socket->peerAddress().toString() << ":" << socket->peerPort();
}

void myserver::handleRequest()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    if (!socket) {
        return;
    }
    QByteArray data = socket->readAll();
    qDebug() << "Data received:" << data;

    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
    QJsonObject jsonObj = jsonDoc.object();

    QString password = jsonObj["password"].toString();

    QByteArray hashedPassword = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);
    jsonObj["password"] = QString(hashedPassword.toHex());
    QJsonDocument updatedJsonDoc(jsonObj);
    QByteArray updatedData = updatedJsonDoc.toJson();

    bool success = saveuser(updatedData);

    QString message;
    if (success) {
        message =  "Information saved successfully.";
    } else {
        message =  "Failed to save information.";
    }
    socket->write(message.toUtf8());
    socket->flush();

    QJsonObject response;
    response["status"] = "success";
    QJsonDocument responseDoc(response);
    socket->write(responseDoc.toJson());
    socket->disconnectFromHost();

}
bool myserver::saveuser(const QByteArray &data)
{
    if (userfile && userfile->isOpen()) {
        QTextStream out(userfile);
        out << data << "\n";
        return true;

    } else {
        qDebug() << "file is not open for writing";
        return false;

    }
}
void myserver::disconnected()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    if (socket) {
        socket->deleteLater();
    }
}
