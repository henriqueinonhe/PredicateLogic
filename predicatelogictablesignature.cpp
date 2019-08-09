#include "predicatelogictablesignature.h"
#include "universaltoken.h"
#include "existentialtoken.h"
#include "bindingrecord.h"
#include "bindingtoken.h"
#include <QDataStream>
#include "punctuationtoken.h"
#include "variabletoken.h"

PredicateLogicTableSignature::PredicateLogicTableSignature() :
    TableSignature()
{
    //Propositional Connectives
    addToken(CoreToken("~", Type("o->o")));
    addToken(CoreToken("^", Type("[o,o]->o")));
    addToken(CoreToken("v", Type("[o,o]->o")));
    addToken(CoreToken("->", Type("[o,o]->o")));
    addToken(CoreToken("<->", Type("[o,o]->o")));

    //Quantifiers
    BindingRecord bindingRecord(0, QVector<unsigned int>({1}));
    QVector<BindingRecord> records({bindingRecord});

    addToken(BindingToken("U", Type("[i,o]->o"), records));
    addToken(BindingToken("E", Type("[i,o]->o"), records));
}

PredicateLogicTableSignature::PredicateLogicTableSignature(QDataStream &stream) :
    TableSignature(stream)
{

}

unique_ptr<Token> PredicateLogicTableSignature::deserializeTokenPtr(QDataStream &stream) const
{
    QString tokenClass;
    stream >> tokenClass;

    if(tokenClass == "PunctuationToken")
    {
        return unique_ptr<Token>(new PunctuationToken(stream));
    }
    else if(tokenClass == "CoreToken")
    {
        return unique_ptr<Token>(new CoreToken(stream));
    }
    else if(tokenClass == "BindingToken")
    {
        return unique_ptr<Token>(new BindingToken(stream));
    }
    else if(tokenClass == "VariableToken")
    {
        return unique_ptr<Token>(new VariableToken(stream));
    }
    else if(tokenClass == "UniversalToken")
    {
        return unique_ptr<Token>(new UniversalToken(stream));
    }
    else if(tokenClass == "ExistentialToken")
    {
        return unique_ptr<Token>(new ExistentialToken(stream));
    }
    else
    {
        QString errorMsg;
        errorMsg += "\"";
        errorMsg += tokenClass;
        errorMsg += "\" is not a valid token class!";
        throw invalid_argument(errorMsg.toStdString());
    }
}


