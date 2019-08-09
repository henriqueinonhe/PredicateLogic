#ifndef PREDICATELOGICUNIVERSALELIMINATION_H
#define PREDICATELOGICUNIVERSALELIMINATION_H

#include "inferenceruleargumentprototype.h"
#include "inferencerulesauxiliarytools.h"
#include "inferencerule.h"

class PredicateLogicUniversalElimination final : public InferenceRule
{
public:
    PredicateLogicUniversalElimination() = default;

    QString name() const override;
    QString callCommand() const override;

    std::shared_ptr<LineOfProof> apply(const Parser &parser, Proof &proof, const QStringList &argumentList) const override;
};

#endif // PREDICATELOGICUNIVERSALELIMINATION_H
