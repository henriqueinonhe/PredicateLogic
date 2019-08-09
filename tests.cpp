#include "catch.hpp"
#include <QBuffer>
#include <QDataStream>
#include "universaltoken.h"
#include "existentialtoken.h"
#include "predicatelogictablesignature.h"
#include "punctuationtoken.h"
#include "bindingtoken.h"
#include "bindingrecord.h"
#include "predicatelogicuniversalelimination.h"
#include "variabletoken.h"
#include "proofwithhypothesis.h"
#include "parser.h"
#include "signature.h"
#include "lineofproof.h"
#include "../General Sources/catchprinters.hpp"
#include "prooftester.h"
#include "predicatelogicexistentialintroduction.h"

TEST_CASE("Universal Token")
{
    //Inherits all invariants from CoreToken

    //tokeClass() Post Conditions
    CHECK(UniversalToken("a", Type("i")).tokenClass() == "UniversalToken");

    //getAllocatedClone() Post Conditions
    const auto t1 = UniversalToken("a", Type("i"));
    const auto ptr = static_cast<const CoreToken *>(t1.getAllocatedClone().get());
    const auto tokenPtr = t1.getAllocatedClone();
    CHECK(ptr->tokenClass() == "UniversalToken");
    CHECK(ptr->getString() == "a");
    CHECK(ptr->getType() == Type("i"));

    //Serialization
    QBuffer buffer;
    QDataStream stream(&buffer);
    buffer.open(QIODevice::WriteOnly);

    SECTION("Using Token As Base")
    {
        stream << *tokenPtr;
        buffer.close();

        buffer.open(QIODevice::ReadOnly);
        QString tokenClassString;
        stream >> tokenClassString;
        UniversalToken t2(stream);

        CHECK(tokenClassString == "UniversalToken");
        CHECK(t2 == t1);
    }

    SECTION("Using CoreToken As Base")
    {
        stream << *ptr;
        buffer.close();

        buffer.open(QIODevice::ReadOnly);
        QString tokenClassString;
        stream >> tokenClassString;
        UniversalToken t2(stream);

        CHECK(tokenClassString == "UniversalToken");
        CHECK(t2 == t1);
    }
}

TEST_CASE("Existential Token")
{
    //Inherits all invariants from CoreToken

    //tokeClass() Post Conditions
    CHECK(ExistentialToken("a", Type("i")).tokenClass() == "ExistentialToken");

    //getAllocatedClone() Post Conditions
    const auto t1 = ExistentialToken("a", Type("i"));
    const auto ptr = static_cast<const CoreToken *>(t1.getAllocatedClone().get());
    const auto tokenPtr = t1.getAllocatedClone();
    CHECK(ptr->tokenClass() == "ExistentialToken");
    CHECK(ptr->getString() == "a");
    CHECK(ptr->getType() == Type("i"));

    //Serialization
    QBuffer buffer;
    QDataStream stream(&buffer);
    buffer.open(QIODevice::WriteOnly);

    SECTION("Using Token As Base")
    {
        stream << *tokenPtr;
        buffer.close();

        buffer.open(QIODevice::ReadOnly);
        QString tokenClassString;
        stream >> tokenClassString;
        ExistentialToken t2(stream);

        CHECK(tokenClassString == "ExistentialToken");
        CHECK(t2 == t1);
    }

    SECTION("Using CoreToken As Base")
    {
        stream << *ptr;
        buffer.close();

        buffer.open(QIODevice::ReadOnly);
        QString tokenClassString;
        stream >> tokenClassString;
        ExistentialToken t2(stream);

        CHECK(tokenClassString == "ExistentialToken");
        CHECK(t2 == t1);
    }
}

TEST_CASE("PredicateLogicTableSignature")
{
    //Class Invariants
    PredicateLogicTableSignature signature;
    BindingRecord bindingRecord(0, QVector<unsigned int>({1}));
    QVector<BindingRecord> records({bindingRecord});
    CHECK(*signature.getTokenPointer("(") == PunctuationToken("("));
    CHECK(*signature.getTokenPointer(")") == PunctuationToken(")"));
    CHECK(*signature.getTokenPointer("~") == CoreToken("~", Type("o->o")));
    CHECK(*signature.getTokenPointer("^") == CoreToken("^", Type("[o,o]->o")));
    CHECK(*signature.getTokenPointer("v") == CoreToken("v", Type("[o,o]->o")));
    CHECK(*signature.getTokenPointer("->") == CoreToken("->", Type("[o,o]->o")));
    CHECK(*signature.getTokenPointer("<->") == CoreToken("<->", Type("[o,o]->o")));
    CHECK(*signature.getTokenPointer("U") == BindingToken("U", Type("[i,o]->o"), records));
    CHECK(*signature.getTokenPointer("E") == BindingToken("E", Type("[i,o]->o"), records));

    //Serialization
    QBuffer buffer;
    QDataStream stream(&buffer);
    buffer.open(QIODevice::WriteOnly);

    SECTION("Using Signature As Base")
    {
        stream << static_cast<const Signature &>(signature);
        buffer.close();
        buffer.open(QIODevice::ReadOnly);
        PredicateLogicTableSignature sig(stream);
        CHECK(*sig.getTokenPointer("(") == PunctuationToken("("));
        CHECK(*sig.getTokenPointer(")") == PunctuationToken(")"));
        CHECK(*sig.getTokenPointer("~") == CoreToken("~", Type("o->o")));
        CHECK(*sig.getTokenPointer("^") == CoreToken("^", Type("[o,o]->o")));
        CHECK(*sig.getTokenPointer("v") == CoreToken("v", Type("[o,o]->o")));
        CHECK(*sig.getTokenPointer("->") == CoreToken("->", Type("[o,o]->o")));
        CHECK(*sig.getTokenPointer("<->") == CoreToken("<->", Type("[o,o]->o")));
        CHECK(*sig.getTokenPointer("U") == BindingToken("U", Type("[i,o]->o"), records));
        CHECK(*sig.getTokenPointer("E") == BindingToken("E", Type("[i,o]->o"), records));
    }

    SECTION("Using TableSignature As Base")
    {
        stream << static_cast<const TableSignature &>(signature);
        buffer.close();
        buffer.open(QIODevice::ReadOnly);
        PredicateLogicTableSignature sig(stream);
        CHECK(*sig.getTokenPointer("(") == PunctuationToken("("));
        CHECK(*sig.getTokenPointer(")") == PunctuationToken(")"));
        CHECK(*sig.getTokenPointer("~") == CoreToken("~", Type("o->o")));
        CHECK(*sig.getTokenPointer("^") == CoreToken("^", Type("[o,o]->o")));
        CHECK(*sig.getTokenPointer("v") == CoreToken("v", Type("[o,o]->o")));
        CHECK(*sig.getTokenPointer("->") == CoreToken("->", Type("[o,o]->o")));
        CHECK(*sig.getTokenPointer("<->") == CoreToken("<->", Type("[o,o]->o")));
        CHECK(*sig.getTokenPointer("U") == BindingToken("U", Type("[i,o]->o"), records));
        CHECK(*sig.getTokenPointer("E") == BindingToken("E", Type("[i,o]->o"), records));
    }
}

TEST_CASE("PredicateLogicUniversalElimintation")
{
    PredicateLogicUniversalElimination rule;

    PredicateLogicTableSignature signature;
    signature.addToken(CoreToken("R", Type("[i,i]->o")));
    signature.addToken(CoreToken("P", Type("i->o")));
    signature.addToken(CoreToken("a", Type("i")));
    signature.addToken(CoreToken("b", Type("i")));
    signature.addToken(VariableToken("x", Type("i")));
    signature.addToken(VariableToken("y", Type("i")));

    Parser parser(&signature, Type("o"));

    QVector<Formula> premises;
    premises.push_back(parser.parse("(U x (P x))"));
    premises.push_back(parser.parse("(U x (-> (P x) (P a)) )"));
    premises.push_back(parser.parse("(U y (U x (R x y) ) )"));
    premises.push_back(parser.parse("(U x (U y (-> (R x y) (R y x))))"));
    const auto conclusion = parser.parse("(P b)");

    auto proof = Proof::createNewProof<ProofWithHypothesis>(0, "", "", premises, conclusion);

    //Pre Conditions

    //Post Conditions
    CHECK(rule.apply(parser, *proof, QStringList({"1", "a"}))->getFormula().formattedString() == "(P a)");
    CHECK(rule.apply(parser, *proof, QStringList({"2", "a"}))->getFormula().formattedString() == "(-> (P a) (P a))");
    CHECK(rule.apply(parser, *proof, QStringList({"3", "b"}))->getFormula().formattedString() == "(U x (R x b))");
    CHECK(rule.apply(parser, *proof, QStringList({"4", "b"}))->getFormula().formattedString() == "(U y (-> (R b y) (R y b)))");
}

TEST_CASE("PredicateLogicExistentialIntroduction")
{
    PredicateLogicExistentialIntroduction rule;

    PredicateLogicTableSignature signature;
    signature.addToken(CoreToken("R", Type("[i,i]->o")));
    signature.addToken(CoreToken("P", Type("i->o")));
    signature.addToken(CoreToken("a", Type("i")));
    signature.addToken(CoreToken("b", Type("i")));
    signature.addToken(VariableToken("x", Type("i")));
    signature.addToken(VariableToken("y", Type("i")));

    Parser parser(&signature, Type("o"));

    QVector<Formula> premises;
    premises.push_back(parser.parse("(P a)"));
    premises.push_back(parser.parse("(R a b)"));
    premises.push_back(parser.parse("(U x (-> (P x) (P a)))"));
    premises.push_back(parser.parse("(^ (^ (P a) (P b) ) (^ (R a a) (P a) ))"));
    const auto conclusion = parser.parse("(P b)");

    auto proof = Proof::createNewProof<ProofWithHypothesis>(0, "", "", premises, conclusion);

     //Pre Conditions
    CHECK_THROWS(rule.apply(parser, *proof, QStringList({"1", "P", "1", "x"})));
    CHECK_THROWS(rule.apply(parser, *proof, QStringList({"1", "a", "1", "b"})));
    CHECK_THROWS(rule.apply(parser, *proof, QStringList({"1", "b", "1", "y"})));

    //Post Conditions
    CHECK(rule.apply(parser, *proof, QStringList({"1", "a", "1", "x"}))->getFormula().formattedString() == "(E x (P x))");
    CHECK(rule.apply(parser, *proof, QStringList({"2", "b", "1", "x"}))->getFormula().formattedString() == "(E x (R a x))");
    CHECK(rule.apply(parser, *proof, QStringList({"3", "a", "1", "y"}))->getFormula().formattedString() == "(E y (U x (-> (P x) (P y))))");
    CHECK(rule.apply(parser, *proof, QStringList({"4", "a", "1,3,4", "x"}))->getFormula().formattedString() == "(E x (^ (^ (P x) (P b)) (^ (R a x) (P x))))");
}
