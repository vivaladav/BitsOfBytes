#-------------------------------------------------
#
# Project created by QtCreator 2016-11-20T23:40:23
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SimpleHackerNewsReader
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    StoryEntry.cpp

HEADERS  += MainWindow.h \
    StoryEntry.h
