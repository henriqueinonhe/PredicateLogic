#ifndef PREDICATELOGICEXISTENTIALINTRODUCTION_H
#define PREDICATELOGICEXISTENTIALINTRODUCTION_H

#include "inferencerule.h"

class PredicateLogicExistentialIntroduction final : public InferenceRule
{
public:
    PredicateLogicExistentialIntroduction();

    QString name() const override;
    QString callCommand() const override;

    std::shared_ptr<LineOfProof> apply(const Parser &parser, Proof &proof, const QStringList &argumentList) const override;

private:
    QVector<unsigned int> extractOccurrences(const QString &string) const;
};

#endif // PREDICATELOGICEXISTENTIALINTRODUCTION_H
