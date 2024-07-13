#include "questiondialog.h"
#include "ui_questiondialog.h"

#include <QButtonGroup>
#include <QDialog>
#include<QDebug>
#include <QLabel>
#include <QLayout>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QRadioButton>
#include <QSpinBox>
#include <QVBoxLayout>
#include<QTimer>
#include "MultipleChoiceQuestion.h"
#include "NumberQuestion.h"
#include "ShortQuestion.h"

questionDialog::questionDialog(Question &question, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::questionDialog)
    ,question(question)
    ,timer(new QTimer(this)),
    timeLeft(20)

{
    ui->setupUi(this);
    connect(timer, &QTimer::timeout, this, &questionDialog::updateProgressBar);
    connect(timer, &QTimer::timeout, this, &questionDialog::timeout);
    timer->start(1000);/*
     ui->categorylabel->setFont(QFont("Tahoma", 12));
     ui->categorylabel->setLayoutDirection(Qt::RightToLeft);*/
     ui->categorylabel->setText(question.getCategory());

    QVBoxLayout *layout = new QVBoxLayout(this);
    ui->questionlabel->setText(question.getQuestionText());
    qDebug()<<"test"<<question.getQuestionText();
    // questionLabel = new QLabel(question.getQuestionText(), this);
    // layout->addWidget(questionlabel);

    if (dynamic_cast<MultipleChoiceQuestion *>(&question)) {
        MultipleChoiceQuestion *mcq = dynamic_cast<MultipleChoiceQuestion *>(&question);
        radioGroup = new QButtonGroup(this);
        QVBoxLayout *radioLayout = new QVBoxLayout();
        for (const QString &choice : mcq->getChoices()) {
            QRadioButton *radioButton = new QRadioButton(choice, this);
            radioGroup->addButton(radioButton);
            radioLayout->addWidget(radioButton);
            answerRadioButtons.append(radioButton);
        }
        answerWidget = new QWidget(this);
        answerWidget->setLayout(radioLayout);
        layout->addWidget(answerWidget);
    } else if (dynamic_cast<NumberQuestion *>(&question)) {
        answerSpinBox = new QSpinBox(this);
        answerSpinBox->setMinimum(INT_MIN);
        answerSpinBox->setMaximum(INT_MAX);
        layout->addWidget(answerSpinBox);
    } else if (dynamic_cast<ShortQuestion *>(&question)) {
        answerLineEdit = new QLineEdit(this);
        layout->addWidget(answerLineEdit);
    }


}

void questionDialog::checkanswer() {
    QString userAnswer;

    if (dynamic_cast<MultipleChoiceQuestion*>(&question)) {
        for (QRadioButton *radioButton : answerRadioButtons) {
            if (radioButton->isChecked()) {
                userAnswer = radioButton->text();
                break;
            }
        }
    } else if (dynamic_cast<NumberQuestion*>(&question)) {
        userAnswer = QString::number(answerSpinBox->value());
    } else if (dynamic_cast<ShortQuestion*>(&question)) {
        userAnswer = answerLineEdit->text();
    }

    if (question.checkAnswer(userAnswer)) {
        accept();

    } else {
        QMessageBox::warning(this, "Incorrect", "The answer is incorrect. Try again.");

    }
}
questionDialog::~questionDialog()
{
    delete ui;
}


void questionDialog::on_skip_clicked()
{
    this->hide();
}


void questionDialog::on_submit_clicked()
{
    checkanswer();
}

void questionDialog::updateProgressBar()
{
    timeLeft--;
    ui->progressBar->setValue(timeLeft);
    if (timeLeft <= 0) {
        timer->stop();
        emit timeout();
        reject();
    }
}
