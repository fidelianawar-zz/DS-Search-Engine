TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    DocumentProcessor.cpp \
    IndexHandler.cpp \
    Porter2_Stemmer.cpp \
    ProgramInterface.cpp \
    StopWords.cpp \
    Word.cpp \
    indexAVL.cpp \
    indexHash.cpp \
    queryProcessor.cpp

HEADERS += \
    AVLIndex.h \
    DocumentProcessor.h \
    DocumentProcessor.h \
    IndexHandler.h \
    IndexInterface.h \
    IndexInterface.h \
    Porter2_Stemmer.h \
    StopWords.h \
    Word.h \
    dsavltree.h \
    dsavltree.h \
    dsavltree.h \
    indexAVL.h \
    indexHash.h \
    indexHash.h \
    json.hpp \
    json.hpp
