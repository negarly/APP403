#include "mainwindow.h"
#include "signup.h"
#include"topicwindow.h"

#include <QApplication>
#include <QMainWindow>
#include <QObject>
#include <QWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    signup *signupwindow = new signup(nullptr);
    MainWindow *firstwindow = new MainWindow(nullptr, signupwindow);
    firstwindow->show();
    return a.exec();
}
