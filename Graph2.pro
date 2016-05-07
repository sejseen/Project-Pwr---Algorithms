#-------------------------------------------------
#
# Project created by QtCreator 2016-05-06T14:21:42
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = Graph2
CONFIG += c++11
CONFIG += c++14
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    Graph.cpp \
    Matrix.cpp \
    Representation.cpp \
    Neighboorlist.cpp \
    Stoper.cpp

HEADERS += \
    Graph.h \
    Matrix.h \
    Representation.h \
    Neighboorlist.h \
    Stoper.h

OTHER_FILES += \
    testDataShortest.txt \
    testMST.txt
