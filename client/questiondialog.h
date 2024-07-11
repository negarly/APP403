#ifndef QUESTIONDIALOG_H
#define QUESTIONDIALOG_H

#include <QDialog>
#include "question.h"

class QLabel;
class QLineEdit;
class QSpinBox;
class QRadioButton;
class QButtonGroup;
class QPushButton;


namespace Ui {
class questionDialog;
}
class questionDialog : public QDialog {
    Q_OBJECT

public:
    questionDialog(Question &question, QWidget *parent = nullptr);
    ~questionDialog();

private slots:
    void checkanswer();
    void on_submit_clicked();
    void updateProgressBar();
    void on_skip_clicked();

signals:
    void timeout();

private:
    Ui::questionDialog *ui;

    Question &question;
    QLabel *questionLabel;
    QLineEdit *answerLineEdit;
    QSpinBox *answerSpinBox;
    QVector<QRadioButton*> answerRadioButtons;
    QButtonGroup *radioGroup;
    QPushButton *submitButton;
    QPushButton *skipButton;
    QWidget *answerWidget;
    QTimer *timer;
    int timeLeft;
};
#endif // QUESTIONDIALOG_H
