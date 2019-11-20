TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
        readIndexFile.cpp

HEADERS += \
    dsavltree.h \
    dshashtable.h \
    json.hpp \
    readIndexFile.h

DISTFILES += \
    ../../../CSE2341-F19-Fidelia-Nawar/Sprint5/build-FinalProject-Desktop_Qt_5_10_0_GCC_64bit-Debug/101310.json
