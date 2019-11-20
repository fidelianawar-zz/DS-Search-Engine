TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        DocumentProcessor.cpp \
        IndexInterface.cpp \
        ProgramInterface.cpp \
        Word.cpp \
        porter2_stemmer.cpp \
        stopwords.cpp

HEADERS += \
    DocumentProcessor.h \
    IndexHandler.h \
    IndexInterface.h \
    Word.h \
    dsavltree.h \
    json.hpp \
    porter2_stemmer.h \
    stopwords.h
