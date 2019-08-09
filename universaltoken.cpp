#include "universaltoken.h"

#include <QString>

UniversalToken::UniversalToken(const QString &string, const Type &type) :
    CoreToken(string, type)
{

}

UniversalToken::UniversalToken(QDataStream &stream) :
    CoreToken(stream)
{

}

QString UniversalToken::tokenClass() const
{
    return "UniversalToken";
}

unique_ptr<Token> UniversalToken::getAllocatedClone() const
{
    return unique_ptr<UniversalToken>(new UniversalToken(*this));
}

QDataStream &operator <<(QDataStream &stream, const UniversalToken &token)
{
    token.serialize(stream);
    return stream;
}
