#include "question.h"

Question::Question(const QString &questionText, const QString &correctAnswer, const QString &category)
    : questionText(questionText), correctAnswer(correctAnswer),category(category) {}

QString Question::getQuestionText() const {
    return questionText;
}

QString Question::getCorrectAnswer() const {
    return correctAnswer;
}
QString Question::getCategory() const{
    return category;

}
