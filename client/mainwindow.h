#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include"signup.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr,signup *_signup=nullptr);
    ~MainWindow();

private slots:

    void on_signup_clicked();

private:
    Ui::MainWindow *ui;
    signup *_signup;

};
#endif // MAINWINDOW_H
