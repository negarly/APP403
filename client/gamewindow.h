#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QTimer>
#include <QVBoxLayout>
#include <QLabel>
#include <QStringList>
#include<QTcpSocket>
#include <QMetaObject>
#include <QRegularExpression>
#include <QPushButton>
#include <QGridLayout>
#include <QVector>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QMessageBox>

#include "Question.h"

namespace Ui {
class gamewindow;
}

class gamewindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit gamewindow(QWidget *parent = nullptr);
    void fetchQuestions(const QString &url);

    ~gamewindow();
private slots:
    // void changeBackground();
    void socket_connected();
    void socket_disconnected();
    void readSocketData();
    void socket_error(QAbstractSocket::SocketError error);

    void handleButtonClick();
    void onQuestionsFetched(QNetworkReply *reply);

private:
    Ui::gamewindow *ui;
    QTcpSocket *socket;

    int currentBackgroundIndex;
    QStringList  backgrounds;
    QLabel *backgroundLabel;


    QGridLayout *gridLayout;
    QGridLayout *existingLayout;

    QPushButton *buttons[9];
    int questionsFetchedCount;

    QVector<Question*> questions;
    QTcpSocket *tcpSocket;
    QNetworkAccessManager *networkManager;
    int currentPlayer;

     void fetchQuestions();

    void handleQuestion(const QJsonObject &jsonObj);
    int questionsNumber, questionsShort, questionsMultiple;
     QMap<QString, QString> buttonOwner;

protected:
    void showEvent(QShowEvent *event) override;
    void closeEvent(QCloseEvent *event) override;
};

#endif // GAMEWINDOW_H
