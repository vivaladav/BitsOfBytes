QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \ 
    TestIntBitset.cpp \
    IntBitSet.cpp

HEADERS += \
    IntBitset.h \
    TestIntBitset.h
