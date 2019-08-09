#ifndef PREDICATELOGICTABLESIGNATURE_H
#define PREDICATELOGICTABLESIGNATURE_H

#include "tablesignature.h"

class PredicateLogicTableSignature : public TableSignature
{
public:
    PredicateLogicTableSignature();
    PredicateLogicTableSignature(const PredicateLogicTableSignature &) = default;
    PredicateLogicTableSignature(PredicateLogicTableSignature &&) noexcept = default;
    PredicateLogicTableSignature &operator =(const PredicateLogicTableSignature &) = default;
    PredicateLogicTableSignature &operator =(PredicateLogicTableSignature &&) noexcept = default;
    ~PredicateLogicTableSignature() noexcept = default;

    PredicateLogicTableSignature(QDataStream &stream);

protected:
    unique_ptr<Token> deserializeTokenPtr(QDataStream &stream) const override;

    friend QDataStream &operator <<(QDataStream &stream, const PredicateLogicTableSignature &signature);
    friend QDataStream &operator >>(QDataStream &stream, PredicateLogicTableSignature &signature);
};

QDataStream &operator <<(QDataStream &stream, const PredicateLogicTableSignature &signature);
QDataStream &operator >>(QDataStream &stream, PredicateLogicTableSignature &signature);

#endif // PREDICATELOGICTABLESIGNATURE_H
