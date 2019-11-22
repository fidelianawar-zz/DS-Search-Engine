TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        DocumentProcessor.cpp \
        IndexHandler.cpp \
        ProgramInterface.cpp \
        Word.cpp \
        indexAVL.cpp \
        indexHash.cpp \
        porter2_stemmer.cpp \
        stopwords.cpp

HEADERS += \
    DocumentProcessor.h \
    IndexHandler.h \
    IndexInterface.h \
    Word.h \
    dsavltree.h \
    indexAVL.h \
    indexHash.h \
    json.hpp \
    porter2_stemmer.h \
    stopwords.h
