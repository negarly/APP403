#ifndef SIGNUP_H
#define SIGNUP_H

#include "topicwindow.h"
#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QTcpSocket>
#include <QJsonObject>
#include <QJsonDocument>
#include<QString>
#include <QMetaObject>
#include <QRegularExpression>
#include <QJsonArray>


namespace Ui {
class signup;
}
// QT_END_NAMESPACE

class signup : public QMainWindow
{
    Q_OBJECT

public:
    signup(QWidget *parent = nullptr);
    ~signup();
signals:
    void signUpComplete(const QString& username);

private slots:

    void on_signupButton_clicked();
    void socket_connected();
    void socket_disconnected();
    void readSocketData();
    void socket_error(QAbstractSocket::SocketError error);

private:
    Ui::signup *ui;
    QTcpSocket *socket;
    topicwindow *_topicwindow;

protected:
    void showEvent(QShowEvent *event) override;
    void closeEvent(QCloseEvent *event) override;
};

#endif // SIGNUP_H
