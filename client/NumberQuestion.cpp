#include "numberquestion.h"


NumberQuestion::NumberQuestion(const QString &questionText, int correctAnswe, const QString &categoryr)
    : Question(questionText, QString::number(correctAnswer),category), correctAnswer(correctAnswer) {}

bool NumberQuestion::checkAnswer(const QString &userAnswer) const {
    bool ok;
    int answer = userAnswer.toInt(&ok);
    return ok && (answer == correctAnswer);
}

QString NumberQuestion::getQuestionType() const {
    return "Number";
}
