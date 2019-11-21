TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
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
