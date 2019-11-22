TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
<<<<<<< HEAD
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
=======
        Porter2_Stemmer.cpp \
        StopWords.cpp \
        main.cpp \
        queryProcessor.cpp \
        readIndexFile.cpp

HEADERS += \
    Porter2_Stemmer.h \
    StopWords.h \
    dsavltree.h \
    dshashtable.h \
    json.hpp \
    queryProcessor.h \
    readIndexFile.h

DISTFILES += \
    ../../../CSE2341-F19-Fidelia-Nawar/Sprint5/build-FinalProject-Desktop_Qt_5_10_0_GCC_64bit-Debug/101310.json \
    ../build-SearchEngine-Desktop_Qt_5_10_0_GCC_64bit-Debug/stopWords.txt
>>>>>>> origin/FideliaBranch
