#-------------------------------------------------
#
# Project created by QtCreator 2013-05-20T16:22:41
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = RubyLike
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    src/lex.cpp \
    src/tablesymbol.cpp \
    src/file.cpp \
    src/tokentype.cpp \
    src/producerlist.cpp \
    src/syntactic.cpp \
    src/semantic.cpp

HEADERS += \
    src/lex.h \
    src/Defs.h \
    src/tablesymbol.h \
    src/file.h \
    src/tokentype.h \
    src/producerlist.h \
    src/syntactic.h \
    src/semantic.h
