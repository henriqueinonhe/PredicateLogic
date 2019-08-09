#include "existentialtoken.h"

ExistentialToken::ExistentialToken(const QString &string, const Type &type) :
    CoreToken(string, type)
{

}

ExistentialToken::ExistentialToken(QDataStream &stream) :
    CoreToken(stream)
{

}

QString ExistentialToken::tokenClass() const
{
    return "ExistentialToken";
}

unique_ptr<Token> ExistentialToken::getAllocatedClone() const
{
    return unique_ptr<ExistentialToken>(new ExistentialToken(*this));
}

QDataStream &operator <<(QDataStream &stream, const ExistentialToken &token)
{
    token.serialize(stream);
    return stream;
}
