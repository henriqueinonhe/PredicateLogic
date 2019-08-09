#include "predicatelogicexistentialintroduction.h"
#include "parser.h"
#include "proofwithhypothesis.h"
#include "inferenceruleargumentprototype.h"
#include "inferencerulesauxiliarytools.h"
#include "lineofproof.h"
#include "signature.h"
#include "propositionalutils.h"
#include "token.h"

PredicateLogicExistentialIntroduction::PredicateLogicExistentialIntroduction()
{

}

QString PredicateLogicExistentialIntroduction::name() const
{
    return "Predicate Logic Existential Introduction";
}

QString PredicateLogicExistentialIntroduction::callCommand() const
{
    return "ExI";
}

std::shared_ptr<LineOfProof> PredicateLogicExistentialIntroduction::apply(const Parser &parser, Proof &proof, const QStringList &argumentList) const
{
    //Pseudo Algorithm
    //Arguments:
    //1. Line Number that contains the formula
    //2. The token that should be substituted by the dummy variable
    //3. A stringnized vector that tells which occurences of the aforementioned token should be substituted
    //4. The token that should act as the dummy variable (must be a variable of course).

    //Algorithm:
    //1. Validate and extract 3rd argument numbers
    //2. Check if occurrences informed by 3rd argument actually exists within the formula (a simple counting and comparing will do)
    //3. Replace the occurrences by the dummy variable
    //4. "Encase" within the existential operator
    //5. Create Line Of Proof

    ArgumentPrototype lineNumberProto = ArgumentPrototype(ArgumentPrototype::ArgumentClass::LineNumber);
    ArgumentPrototype beforeTokenProto = ArgumentPrototype(ArgumentPrototype::ArgumentClass::Token);
    ArgumentPrototype occurrencesVectorProto = ArgumentPrototype(ArgumentPrototype::ArgumentClass::String);
    ArgumentPrototype dummyVariableProto = ArgumentPrototype(ArgumentPrototype::ArgumentClass::Token);
    QVector<ArgumentPrototype> prototypes({lineNumberProto, beforeTokenProto, occurrencesVectorProto, dummyVariableProto});
    InferenceRulesAuxiliaryTools::checkArgumentListCompliance(parser, argumentList, prototypes, QVector<int>({4}));

    const auto lineNumber = argumentList[0].toInt();
    const auto premiss = proof.getLineOfProof(lineNumber).getFormula();
    auto premissTokenString = premiss.getParsingTree().getTokenString();
    const auto &beforeToken = *parser.getSignature()->getTokenPointer(argumentList[1]);
    const auto occurrences = extractOccurrences(argumentList[2]);
    const auto dummyVariableToken = parser.getSignature()->getTokenPointer(argumentList[3]);
    const auto replacedTokenString = premissTokenString.replace(beforeToken, dummyVariableToken, occurrences);

    PropositionalUtils::hypothesisNormalProcedure(proof, QVector<int>({lineNumber}));
    QString conclusionString;
    conclusionString += "(E ";
    conclusionString += dummyVariableToken->getString();
    conclusionString += " ";
    conclusionString += replacedTokenString.formattedString();
    conclusionString += ")";
    const auto conclusionFormula = parser.parse(conclusionString);

    Justification justification(callCommand(), argumentList);
    return shared_ptr<LineOfProof>(new LineOfProof(conclusionFormula, justification));
}

QVector<unsigned int> PredicateLogicExistentialIntroduction::extractOccurrences(const QString &string) const
{
    //Pseudo Algorithm
    //1. Checks is not empty
    //2. Split at ",", do not keep empty parts
    //3. Checks that resulting string list contains only positive numbers greater than 0
    //4. Return occurrences vector

    if(string.isEmpty())
    {
        throw invalid_argument("The occurrences vector cannot be empty!");
    }

    QVector<unsigned int> occurrences;
    const auto occurrencesList = string.split(",", QString::SplitBehavior::SkipEmptyParts);
    for(const auto &occurrence : occurrencesList)
    {
        bool ok;
        const auto occurrenceNumber = occurrence.toUInt(&ok);
        if(!ok)
        {
            QString errorMsg;
            errorMsg += "\"";
            errorMsg += occurrence;
            errorMsg += "\" is not a valid occurrence!";
            throw invalid_argument(errorMsg.toStdString());
        }
        if(occurrenceNumber == 0)
        {
            throw invalid_argument("Occurrence number cannot be 0!");
        }

        occurrences.push_back(occurrenceNumber);
    }

    return occurrences;
}
