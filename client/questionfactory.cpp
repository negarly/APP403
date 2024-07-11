#include "questionfactory.h"
#include<QJsonArray>

// QuestionFactory::QuestionFactory() {}
Question* QuestionFactory::createQuestion(const QJsonObject &jsonObj) {
    QString type = jsonObj["type"].toString();
    if (type == "multiple") {
    QString questionText = jsonObj["questionText "].toString();
    QString correctAnswer = jsonObj["answer"].toString();
    QString category = jsonObj["category "].toString();

    QJsonArray choicesArray = jsonObj["choices"].toArray();
    QVector<QString> choices;
    for (const QJsonValue &value : choicesArray) {
        choices.append(value.toString());
    }

    return new MultipleChoiceQuestion(questionText, correctAnswer,category, choices);
    }

// Function to create a NumberQuestion object
    else if (type == "number") {
    QString questionText = jsonObj["questionText "].toString();
    int correctAnswer = jsonObj["answer"].toInt();
    QString category = jsonObj["category "].toString();


    return new NumberQuestion(questionText, correctAnswer,category );
    }

// Function to create a ShortQuestion object
    else if (type == "short") {
    QString questionText = jsonObj["questionText "].toString();
    QString correctAnswer = jsonObj["answer"].toString();
    QString category = jsonObj["category "].toString();
    return new ShortQuestion(questionText, correctAnswer, category);
    }

    return nullptr; // Return nullptr if the type is unknown
}
