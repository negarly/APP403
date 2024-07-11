#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "QuestionFactory.h"
#include "QuestionDialog.h"
#include <QWidget>
#include <QTimer>
#include <QVBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QDebug>
#include<QJsonDocument>
#include<QJsonObject>
#include<QMessageBox>
#include <QJsonArray>
#include <QRandomGenerator>
#include <QNetworkRequest>
#include<QGridLayout>
#include<QPushButton>
#include <QFont>
#include <random>
#include <QtGlobal>

gamewindow::gamewindow(QWidget *parent)
    : QMainWindow(parent), currentBackgroundIndex(0)
    , ui(new Ui::gamewindow)
    ,currentPlayer(1)
{
    socket = new QTcpSocket(this);

    ui->setupUi(this);
    connect(socket, &QTcpSocket::connected, this, &gamewindow::socket_connected);
    connect(socket, &QTcpSocket::disconnected, this, &gamewindow::socket_disconnected);
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(socket_error(QAbstractSocket::SocketError)));

    connect(socket, &QTcpSocket::readyRead, this, &gamewindow::readSocketData);
    // backgrounds = {"C:/Users/Techno/Downloads/3D_cube_generated.jpg",
    //                "C:/Users/Techno/Downloads/Abstract_hologram_hi-tech_background_generated.jpg",
    //                "C:/Users/Techno/Downloads/vecteezy_hologram-podium-futuristic-circle-blue-vector_8450118.jpg",
    //                "C:/Users/Techno/Downloads/vecteezy_futuristic-sci-fi-glowing-hud-element-and-particle_5550030.jpg",
    //                "C:/Users/Techno/Downloads/Abstract_background_generated.jpg" };

    // QWidget *centralWidget = new QWidget(this);
    // setCentralWidget(centralWidget);

    // QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    // backgroundLabel = new QLabel(centralWidget);
    // layout->addWidget(backgroundLabel);

    // QTimer *timer = new QTimer(this);
    // connect(timer, &QTimer::timeout, this, &gamewindow::changeBackground);
    // timer->start(20000);

    // changeBackground();

    // backgroundLabel->setScaledContents(true);

    // gridLayout = new QGridLayout(centralWidget);
    // QGridLayout *existingLayout = new QGridLayout(centralWidget);
    QWidget *centralWidget = this->centralWidget();
    if (!centralWidget) {
        centralWidget = new QWidget(this);
        this->setCentralWidget(centralWidget);
    }

    // Assuming existing layout is a QGridLayout
    existingLayout = qobject_cast<QGridLayout *>(centralWidget->layout());
    if (!existingLayout) {
        existingLayout = new QGridLayout(centralWidget);
        centralWidget->setLayout(existingLayout);
    }
    QFont buttonFont;
    buttonFont.setPointSize(30);
    qDebug() << "Adding buttons to the layout";
    QString buttonStyle = "background-color: rgb(140, 254, 255);";
    QSize buttonSize(100, 100);

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
           int index = i * 3 + j;
            buttons[index] = new QPushButton(QString("-"), this);
            buttons[index]->setFont(buttonFont);
            buttons[index]->setStyleSheet(buttonStyle);
            buttons[index]->setFixedSize(buttonSize);
            existingLayout->addWidget(buttons[index], i, j);

            connect(buttons[index], &QPushButton::clicked, this, &gamewindow::handleButtonClick);
            qDebug() << "Added Button" << index + 1 << "at" << i << j;

        }
    }

    networkManager = new QNetworkAccessManager(this);
    fetchQuestions();

    connect(networkManager, &QNetworkAccessManager::finished, this, &gamewindow::onQuestionsFetched);

}

void gamewindow::showEvent(QShowEvent *event) {
    QMainWindow::showEvent(event);
    socket->connectToHost("localhost", 1234);
    if (!socket->waitForConnected(2000)) {
        qDebug() << "Error: " << socket->errorString();
    }
}

void gamewindow::closeEvent(QCloseEvent *event) {
    socket->close();
    qDebug()<<"socket closed";

    QMainWindow::closeEvent(event);

}


void gamewindow::fetchQuestions() {

    QString apiUrl ="https://questionbank.liara.run/api/RmF0ZW1lIGhvc2VpbmksbmVnYXIgZWx5YXNpLGlvRGY3b0hFNjY0bA/question?type=number";
    QNetworkRequest request(QUrl("https://questionbank.liara.run/api/RmF0ZW1lIGhvc2VpbmksbmVnYXIgZWx5YXNpLGlvRGY3b0hFNjY0bA/question?type=number"));
    qDebug() << "Sending request to:" << apiUrl;

    networkManager->get(request);
}

void gamewindow::onQuestionsFetched(QNetworkReply *reply) {
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray response = reply->readAll();
        qDebug() << "Received response:" <<response;

        QJsonParseError parseError;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(response, &parseError);
        if (jsonDoc.isNull()) {
            qDebug() << "Failed to parse JSON response:" << parseError.errorString();
            QMessageBox::critical(this, "Error", "Failed to parse JSON response: " + parseError.errorString());
            reply->deleteLater();
            return;
        }
        QJsonObject questionObject = jsonDoc.object();
        qDebug()<<questionObject;

        Question *question = QuestionFactory::createQuestion(questionObject);
        qDebug()<<"the question is:"<<question;

        if (question) {
            questions.append(question);
        }

    } else {
        QMessageBox::warning(this, "Error", "Failed to fetch questions from the server.");
    }
    reply->deleteLater();

}


void gamewindow::handleButtonClick() {
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (button) {
        if (questions.isEmpty()) {
            QMessageBox::warning(this, "Error", "No questions available.");
            return;
        }
        button->setText("...");

        // Select a question randomly
        int index = rand() % questions.size();
        Question *question = questions[index];
        questionDialog dialog(*question, this);
        if (dialog.exec() == QDialog::Accepted) {
            button->setText(currentPlayer == 1 ? "X" : "O");
            button->setEnabled(false);

            QByteArray data = QString::number(gridLayout->indexOf(button)).toUtf8();
            tcpSocket->write(data);

            currentPlayer = (currentPlayer == 1) ? 2 : 1;
        }
        if (dialog.exec() == QDialog::Rejected) {
            button->setText("-");
            button->setEnabled(false);
        }
    }

}

void gamewindow::socket_connected()
{
    qDebug() << "Connected to the server!";
}

void gamewindow::socket_disconnected()
{
    qDebug() << "Disconnected from the server!";
}

void gamewindow::readSocketData()
{
    QByteArray data = socket->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
    if (jsonDoc.isNull()) {
        qDebug() << "Failed to parse JSON.";
        return;
    }

    QJsonObject responseObj = jsonDoc.object();
    qDebug() << responseObj;
    QString message = responseObj["message"].toString();
    qDebug() << message;

    if (message == "WAIT")
    {
        QMessageBox::information(nullptr, "Waiting", "Please wait for another player to join.");
    }

    else if(message=="GAME_ON"){
        QMessageBox::information(nullptr, "Waiting", "game still on.");

    }

    Question *question = QuestionFactory::createQuestion(responseObj);
    qDebug()<<"the question is:"<<question;

    if (question) {
        questions.append(question);
    }
}

void gamewindow::socket_error(QAbstractSocket::SocketError error )
{
    qDebug() << "Socket error: " << socket->errorString();
}/*
void gamewindow:: changeBackground() {
    if (backgrounds.isEmpty())
        return;

    QString imagePath = backgrounds[currentBackgroundIndex];
    QPixmap pixmap(imagePath);
    pixmap = pixmap.scaled(backgroundLabel->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    backgroundLabel->setPixmap(pixmap);
    currentBackgroundIndex = (currentBackgroundIndex + 1) % backgrounds.size();
}*/
gamewindow::~gamewindow()
{
    delete ui;
}
