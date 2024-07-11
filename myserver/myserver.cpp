#include "myserver.h"
// #include "ui_mainwindow.h"

#include <QCryptographicHash>


myserver::myserver(QWidget *parent)
    : QTcpServer(parent)
    , numPlayersReady(0)
{

    if (!listen(QHostAddress::Any, 1234)) {
        qDebug() << "Server could not start!";
    } else {
        qDebug() << "Server started on port" << serverAddress().toString() << ":" << serverPort();
    }

    userfile = new QFile("users.txt");
    if (!userfile->open(QIODevice::Append | QIODevice::Text)) {
        qDebug() << "Unable to open user file";
    }

}

myserver::~myserver()
{
    // delete ui;

}


void myserver::incomingConnection(qintptr socketDescriptor)
{
    QTcpSocket *clientsocket = new QTcpSocket(this);
    clientsocket->setSocketDescriptor(socketDescriptor);
    clients.append(clientsocket);

    connect(clientsocket, &QTcpSocket::readyRead, this, &myserver::handleRequest);
    // connect(clientsocket, &QTcpSocket::disconnected, this, &myserver::disconnected);

    qDebug() << "New connection from" << clientsocket->peerAddress().toString() << ":" << clientsocket->peerPort();


}

void myserver::handleRequest()
{
    QTcpSocket *clientsocket = qobject_cast<QTcpSocket *>(sender());
    if (!clientsocket) {
        return;
    }
    QByteArray data;
    QDataStream in(clientsocket);

    while(!in.atEnd()){
        data.append(clientsocket->readAll());
        if (clientsocket->waitForReadyRead(1000)) continue;
    }

    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
    if (jsonDoc.isNull()) {
        qDebug() << "Failed to parse JSON.";
        return;
    }

    QJsonObject jsonObj = jsonDoc.object();
    qDebug() << "Received JSON array:" << jsonObj;





    //------------AUTHENTICATION-------------

    if (jsonObj["command"] == "signup") {

        QJsonObject userObject = jsonObj["user"].toObject();

        QString username = userObject["username"].toString();
        QString email = userObject["email"].toString();
        QString password = userObject["password"].toString();

        QByteArray hashedPassword = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);
        userObject["password"] = QString(hashedPassword.toHex());
        QJsonDocument updatedJsonDoc(userObject);
        QByteArray updatedData = updatedJsonDoc.toJson();
        bool success = saveuser(updatedData);
         QJsonObject response;

        if (success) {
            response["status"] = "success/Information saved successfully";

        } else {
            response["status"] = "failed/Failed to save information";

        }

        QJsonDocument responseDoc(response);
        clientsocket->write(responseDoc.toJson());


        numPlayersReady++;

        if (numPlayersReady == 2) {
            for (QTcpSocket *client : clients) {
                response["message"] = "START";
                QJsonDocument responseDoc(response);
                clientsocket->write(responseDoc.toJson());

            }
        }
        else if (numPlayersReady < 2) {
            response["message"] = "WAIT";
            QJsonDocument responseDoc(response);
            clients[0]->write(responseDoc.toJson());

            // clients[0]->flush();

        }
        else{
            response["message"] = "GAME_ON";
            QJsonDocument responseDoc(response);
            clientsocket->write(responseDoc.toJson());
            // clientsocket->flush();

        }
    }


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
    QTcpSocket *clientsocket = qobject_cast<QTcpSocket *>(sender());
    clients.removeOne(clientsocket);
    clientsocket->deleteLater();
    // broadcast("A player has disconnected.game over.");
}

void myserver::broadcast(const QString &message)
{
    for (QTcpSocket *client : clients)
    {
        client->write(message.toUtf8());
    }
}
