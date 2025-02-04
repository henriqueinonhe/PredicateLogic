#include "predicatelogicuniversalelimination.h"
#include "parser.h"
#include "proof.h"
#include <QStringList>
#include "signature.h"
#include "lineofproof.h"
#include "propositionalutils.h"
#include "parsingtree.h"
#include "parsingtreeconstiterator.h"
#include "token.h"

QString PredicateLogicUniversalElimination::name() const
{
    return "Predicate Logic Universal Elimination";
}

QString PredicateLogicUniversalElimination::callCommand() const
{
    return "AllE";
}

std::shared_ptr<LineOfProof> PredicateLogicUniversalElimination::apply(const Parser &parser, Proof &proof, const QStringList &argumentList) const
{
    //TODO Refactor
    ArgumentPrototype universalProp(ArgumentPrototype::ArgumentClass::LineNumber);
    ArgumentPrototype instantiatedToken(ArgumentPrototype::ArgumentClass::Token);
    InferenceRulesAuxiliaryTools::checkArgumentListCompliance(parser, argumentList, QVector<ArgumentPrototype>({universalProp, instantiatedToken}), QVector<int>({2}));

    const auto  universalPropLineNumber = argumentList[0].toInt();
    const auto tokenString = argumentList[1];
    const auto token = parser.getSignature()->getTokenPointer(tokenString);
    const auto &lineOfProof = proof.getLineOfProof(universalPropLineNumber);
    const auto universalPropFormula = lineOfProof.getFormula();
    InferenceRulesAuxiliaryTools::checkMainOperator("U", universalPropFormula, 1);

    PropositionalUtils::hypothesisNormalProcedure(proof, QVector<int>({universalPropLineNumber}));

    //Make Conclusion
    const auto tree = universalPropFormula.getParsingTree();
    ParsingTreeConstIterator iter(&tree);
    iter.goToChild(1);
    const auto &dummyVariable = iter->getTokenString().first();
    iter.goToParent();
    iter.goToChild(2);
    auto universalPropTokenString = iter->getTokenString();
    const auto conclusionTokenString = universalPropTokenString.replaceAll(dummyVariable, token);
    //NOTE This replacement doesn't take scope into consideration,
    //but given that parser rules are strict regarding binding tokens, this should not be a problem
    Formula conclusionFormula(conclusionTokenString.formattedString(), parser);

    Justification justification(callCommand(), argumentList);
    return shared_ptr<LineOfProof>(new LineOfProof(conclusionFormula, justification));
}

