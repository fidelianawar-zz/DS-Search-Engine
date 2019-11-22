TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    AVLIndex.cpp \
    DocumentProcessor.cpp \
    IndexHandler.cpp \
    Porter2_Stemmer.cpp \
    ProgramInterface.cpp \
    StopWords.cpp \
    Word.cpp \
    indexAVL.cpp \
    indexHash.cpp \
    queryProcessor.cpp \
    readIndexFile.cpp \
    stopwords.cpp

HEADERS += \
    AVLIndex.h \
    DocumentProcessor.h \
    IndexHandler.h \
    IndexInterface.h \
    Porter2_stemmer.h \
    Word.h \
    dsavltree.h \
    indexAVL.h \
    indexHash.h \
    indexinterface.h \
    json.hpp \
    stopwords.h
