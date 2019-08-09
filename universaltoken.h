#ifndef UNIVERSALTOKEN_H
#define UNIVERSALTOKEN_H

#include "coretoken.h"

class QString;
class QDataStream;

class UniversalToken : public CoreToken
{
public:
    UniversalToken() = delete;
    UniversalToken &operator =(const UniversalToken &) = delete;
    UniversalToken &operator =(UniversalToken &&) = delete;
    virtual ~UniversalToken() noexcept = default;

    UniversalToken(const QString &string, const Type &type);
    UniversalToken(QDataStream &stream);

    virtual QString tokenClass() const override;
    virtual unique_ptr<Token> getAllocatedClone() const override;

protected:
    UniversalToken(const UniversalToken &) = default;
    UniversalToken(UniversalToken &&) noexcept = default;

    friend QDataStream &operator <<(QDataStream &stream, const UniversalToken &token);
};

QDataStream &operator <<(QDataStream &stream, const UniversalToken &token);

#endif // UNIVERSALTOKEN_H
