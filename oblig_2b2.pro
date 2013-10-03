#-------------------------------------------------
#
# Project created by QtCreator 2013-10-03T10:57:48
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = oblig_2b2
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    lib.cpp
LIBS+=-larmadillo -llapack -lblas
