#include "catch.hpp"
#include <QBuffer>
#include <QDataStream>
#include "tablesignature.h"
#include "universaltoken.h"
#include "existentialtoken.h"
#include "predicatelogictablesignature.h"
#include "punctuationtoken.h"
#include "bindingtoken.h"
#include "bindingrecord.h"

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
