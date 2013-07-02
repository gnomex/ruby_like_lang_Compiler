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
    src/attrib.cpp \
    src/ast.cpp \
    src/operator.cpp \
    src/ifelse.cpp \
    src/each.cpp \
    src/tlist.cpp \
    src/syntactic.cpp \
    src/error.cpp

HEADERS += \
    src/lex.h \
    src/Defs.h \
    src/tablesymbol.h \
    src/file.h \
    src/tokentype.h \
    src/producerlist.h \
    src/attrib.h \
    src/ast.h \
    src/operator.h \
    src/ifelse.h \
    src/each.h \
    src/tlist.h \
    src/syntactic.h \
    src/error.h
