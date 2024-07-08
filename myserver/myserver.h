#ifndef MYSERVER_H
#define MYSERVER_H

#include <QMainWindow>

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTextStream>

#include <QFile>/*
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE*/

class myserver : public QTcpServer
{
    Q_OBJECT

public:
    myserver(QWidget *parent = nullptr);
    ~myserver();


protected:
    void incomingConnection(qintptr socketDescriptor) override;

private slots:
    void handleRequest();
    void disconnected();


private:
    // Ui::MainWindow *ui;
     QFile *userfile;
    // QFile *gamestatsfile;

     bool saveuser(const QByteArray &data);
    // bool saveGameStats(const QJsonObject &gameStats);

};
#endif // MYSERVER_H