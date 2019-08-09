TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle

SOURCES += \
        existentialtoken.cpp \
        main.cpp \
        predicatelogictablesignature.cpp \
        tests.cpp \
        universaltoken.cpp

HEADERS += \
    catch.hpp \
    existentialtoken.h \
    predicatelogictablesignature.h \
    universaltoken.h

LIBS += -L"C:/Users/Henrique/Documents/Qt Projects/Static Libraries/Libs/" -llibProofAssistantFramework

PRE_TARGETDEPS += "C:/Users/Henrique/Documents/Qt Projects/Static Libraries/Libs/libProofAssistantFramework.a"

INCLUDEPATH += ../ProofAssistantFramework \
               ../Language/Parser \
               ../Language/Processors \
               ../Language/Processors/PreProcessors \
               ../Language/Processors/PostProcessors \
               ../Language/Token \
               ../Language/Type \
               ../Language/Utils\
