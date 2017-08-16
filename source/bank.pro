#-------------------------------------------------
#
# Project created by QtCreator 2016-08-13T09:26:05
#
#-------------------------------------------------


QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = bank
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    terminal1.cpp \
    globals.cpp \
    terminal2.cpp

HEADERS  += mainwindow.h \
    terminal1.h \
    globals.h \
    terminal2.h

FORMS    += mainwindow.ui \
    terminal1.ui \
    terminal2.ui
QMAKE_CFLAGS_DEBUG += -fopenmp
QMAKE_LIBS += -lgomp
QMAKE_CXXFLAGS += -fopenmp
QMAKE_LFLAGS += -fopenmp
