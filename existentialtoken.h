#ifndef EXISTENTIALTOKEN_H
#define EXISTENTIALTOKEN_H

#include "coretoken.h"

class ExistentialToken : public CoreToken
{
public:
    ExistentialToken() = delete;
    ExistentialToken &operator =(const ExistentialToken &) = delete;
    ExistentialToken &operator =(ExistentialToken &&) = delete;
    virtual ~ExistentialToken() noexcept = default;

    ExistentialToken(const QString &string, const Type &type);
    ExistentialToken(QDataStream &stream);

    virtual QString tokenClass() const override;
    virtual unique_ptr<Token> getAllocatedClone() const override;

protected:
    ExistentialToken(const ExistentialToken &) = default;
    ExistentialToken(ExistentialToken &&) noexcept = default;

    friend QDataStream &operator <<(QDataStream &stream, const ExistentialToken &token);
};

QDataStream &operator <<(QDataStream &stream, const ExistentialToken &token);

#endif // EXISTENTIALTOKEN_H
