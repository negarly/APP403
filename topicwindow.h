#ifndef TOPICWINDOW_H
#define TOPICWINDOW_H
#include"gamewindow.h"

#include <QTcpSocket>

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
namespace Ui {
class topicwindow;
}

class topicwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit topicwindow(const QString &username, const QString &email,QWidget *parent = nullptr);
    ~topicwindow();


private slots:
    void on_pushButton_clicked();

private:
    Ui::topicwindow *ui;
    gamewindow *_gamewindow;
};

#endif // TOPICWINDOW_H
