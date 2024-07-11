#ifndef QUESTIONFACTORY_H
#define QUESTIONFACTORY_H

#include "question.h"

#include <QJsonObject>
#include "Question.h"
#include "MultipleChoiceQuestion.h"
#include "NumberQuestion.h"
#include "ShortQuestion.h"

class QuestionFactory : public Question
{
public:
    // QuestionFactory();
    static Question* createQuestion(const QJsonObject &jsonObj);

};

#endif // QUESTIONFACTORY_H
