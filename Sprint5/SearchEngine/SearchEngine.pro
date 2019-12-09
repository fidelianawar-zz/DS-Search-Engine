TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    DocumentProcessor.cpp \
    IndexAVL.cpp \
    IndexHandler.cpp \
    IndexHash.cpp \
    Porter2_Stemmer.cpp \
    ProgramInterface.cpp \
    QueryProcessor.cpp \
    QuerySearcher.cpp \
    StopWords.cpp \
    Word.cpp

HEADERS += \
    AVLIndex.h \
    DSAVLTree.h \
    DSHashTable.h \
    DocumentProcessor.h \
    DocumentProcessor.h \
    IndexAVL.h \
    IndexHandler.h \
    IndexHash.h \
    IndexInterface.h \
    IndexInterface.h \
    Porter2_Stemmer.h \
    ProgamInterface.h \
    QueryProcessor.h \
    QuerySearcher.h \
    StopWords.h \
    Word.h \
    json.hpp \
    json.hpp
