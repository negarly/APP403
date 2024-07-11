#include "multiplechoicequestion.h"

MultipleChoiceQuestion::MultipleChoiceQuestion(const QString &questionText,
                                               const QString &correctAnswer
                                               , const QString &category,
                                               const QVector<QString> &choices)
    : Question(questionText, correctAnswer,category), choices(choices){}

bool MultipleChoiceQuestion::checkAnswer(const QString &userAnswer) const {
    return userAnswer.trimmed().compare(correctAnswer.trimmed(), Qt::CaseInsensitive) == 0;
}

QString MultipleChoiceQuestion::getQuestionType() const {
    return "Multiple Choice";
}

QVector<QString> MultipleChoiceQuestion::getChoices() const {
    return choices;
}
