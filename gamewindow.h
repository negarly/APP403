#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QTimer>
#include <QVBoxLayout>
#include <QLabel>
#include <QStringList>


namespace Ui {
class gamewindow;
}

class gamewindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit gamewindow(QWidget *parent = nullptr);

    ~gamewindow();
private slots:
    void changeBackground();

private:
    Ui::gamewindow *ui;
    int currentBackgroundIndex;
    QStringList  backgrounds;
    QLabel *backgroundLabel;

};

#endif // GAMEWINDOW_H
