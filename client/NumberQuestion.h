#ifndef NUMBERQUESTION_H
#define NUMBERQUESTION_H

#include "question.h"

class NumberQuestion : public Question {
public:
    NumberQuestion(const QString &questionText, int correctAnswer, const QString &category);

    virtual bool checkAnswer(const QString &userAnswer) const override;
    virtual QString getQuestionType() const override;

private:
    int correctAnswer;
};
#endif // NUMBERQUESTION_H
