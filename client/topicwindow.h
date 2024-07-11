#ifndef TOPICWINDOW_H
#define TOPICWINDOW_H
#include"gamewindow.h"

#include <QTcpSocket>
#include <QMessageBox>
#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMetaObject>
#include <QRegularExpression>
namespace Ui {
class topicwindow;
}

class topicwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit topicwindow(const QString &username, const QString &email,QWidget *parent = nullptr);
    void showWaitingBox();

    ~topicwindow();


private slots:
    void on_pushButton_clicked();
    void socket_connected();
    void socket_disconnected();
    void readSocketData();
    void socket_error(QAbstractSocket::SocketError error);


private:
    Ui::topicwindow *ui;
    gamewindow *_gamewindow;
    QTcpSocket *socket;
    QMessageBox *waitingBox;

protected:
    void showEvent(QShowEvent *event) override;
    void closeEvent(QCloseEvent *event) override;
};

#endif // TOPICWINDOW_H
