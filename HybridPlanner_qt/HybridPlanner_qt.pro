#-------------------------------------------------
#
# Project created by QtCreator 2016-11-05T11:13:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HybridPlanner_qt
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Algs.cpp \
    TyDefFunc.cpp

HEADERS  += mainwindow.h \
    Thread.h \
    Process.h \
    Planner.h \
    TyDefFunc.h \
    Algs.h

FORMS    +=
