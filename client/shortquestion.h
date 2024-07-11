#ifndef SHORTQUESTION_H
#define SHORTQUESTION_H

#include "question.h"

class ShortQuestion : public Question {
public:
    ShortQuestion(const QString &questionText, const QString &correctAnswer, const QString &category);

    virtual bool checkAnswer(const QString &userAnswer) const override;
    virtual QString getQuestionType() const override;
};

#endif // SHORTQUESTION_H
