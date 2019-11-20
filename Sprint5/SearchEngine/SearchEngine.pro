TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        DocumentProcessor.cpp \
        IndexHandler.cpp \
        IndexInterface.cpp \
        ProgramInterface.cpp \
        stopwords.cpp

HEADERS += \
    DocumentProcessor.h \
    IndexHandler.h \
    IndexInterface.h \
    dsavltree.h \
    json.hpp \
    stopwords.h
