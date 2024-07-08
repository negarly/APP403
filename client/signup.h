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
    void onConnected();
    void onReadyRead();


    void on_signupButton_clicked();

private:
    Ui::signup *ui;
    QTcpSocket *socket;
    topicwindow *_topicwindow;

};

#endif // SIGNUP_H
