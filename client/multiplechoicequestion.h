#ifndef MULTIPLECHOICEQUESTION_H
#define MULTIPLECHOICEQUESTION_H

#include "Question.h"
#include <QVector>

class MultipleChoiceQuestion : public Question
{
public:
    MultipleChoiceQuestion(const QString &questionText, const QString &correctAnswer, const QString &category,
                           const QVector<QString> &choices);

    virtual bool checkAnswer(const QString &userAnswer) const override;
    virtual QString getQuestionType() const override;

    QVector<QString> getChoices() const;

private:
    QVector<QString> choices;

};

#endif // MULTIPLECHOICEQUESTION_H
