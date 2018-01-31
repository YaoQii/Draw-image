#-------------------------------------------------
#
# Project created by QtCreator 2018-01-30T16:41:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = paper_Qcustom
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h \
    vector2d.h \
    curve_3.h \
    helper.h

FORMS    += mainwindow.ui
