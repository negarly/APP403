#ifndef QUESTION_H
#define QUESTION_H

#include <QString>

class Question
{
public:
    Question(const QString &questionText, const QString &correctAnswer, const QString &category);
    QString getQuestionText() const;
    QString getCorrectAnswer() const;
    QString getCategory() const;

    ~Question();

    virtual bool checkAnswer(const QString &userAnswer) const = 0;
    virtual QString getQuestionType() const = 0;

protected:
    QString questionText;
    QString correctAnswer;
    QString category;
};

#endif // QUESTION_H
