#include "shortquestion.h"

ShortQuestion::ShortQuestion(const QString &questionText, const QString &correctAnswer, const QString &category )
    : Question(questionText, correctAnswer,category) {}

bool ShortQuestion::checkAnswer(const QString &userAnswer) const {
    return userAnswer.trimmed().compare(correctAnswer.trimmed(), Qt::CaseInsensitive) == 0;
}

QString ShortQuestion::getQuestionType() const {
    return "Short";
}
