TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle

SOURCES += \
        existentialtoken.cpp \
        main.cpp \
        predicatelogicexistentialelimination.cpp \
        predicatelogicexistentialintroduction.cpp \
        predicatelogictablesignature.cpp \
        predicatelogicuniversalelimination.cpp \
        predicatelogicuniversalintroduction.cpp \
        predicatelogicutils.cpp \
        tests.cpp \
        universaltoken.cpp

HEADERS += \
    catch.hpp \
    existentialtoken.h \
    predicatelogicexistentialelimination.h \
    predicatelogicexistentialintroduction.h \
    predicatelogictablesignature.h \
    predicatelogicuniversalelimination.h \
    predicatelogicuniversalintroduction.h \
    predicatelogicutils.h \
    universaltoken.h

LIBS += -L"C:/Users/Henrique/Documents/Qt Projects/Static Libraries/Libs/" -llibPropositionalLogic
LIBS += -L"C:/Users/Henrique/Documents/Qt Projects/Static Libraries/Libs/" -llibProofAssistantFramework

PRE_TARGETDEPS += "C:/Users/Henrique/Documents/Qt Projects/Static Libraries/Libs/libPropositionalLogic.a"
PRE_TARGETDEPS += "C:/Users/Henrique/Documents/Qt Projects/Static Libraries/Libs/libProofAssistantFramework.a"

INCLUDEPATH += ../ProofAssistantFramework \
               ../Language/Parser \
               ../Language/Processors \
               ../Language/Processors/PreProcessors \
               ../Language/Processors/PostProcessors \
               ../Language/Token \
               ../Language/Type \
               ../Language/Utils\
               ../PropositionalLogicPlugins
