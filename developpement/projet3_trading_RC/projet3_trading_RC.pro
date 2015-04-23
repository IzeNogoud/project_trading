#-------------------------------------------------
#
# Project created by QtCreator 2015-03-25T09:53:16
#
#-------------------------------------------------

QT      += core gui
QT      += sql
QT      += widgets
QT      += webkitwidgets
QT      += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = projet3_trading_RC
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    connectiondb.cpp \
    help.cpp \
    faq.cpp \
    config.cpp

HEADERS  += mainwindow.h \
    connectiondb.h \
    help.h \
    faq.h \
    config.h

RESOURCES +=
