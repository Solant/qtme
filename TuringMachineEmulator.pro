#-------------------------------------------------
#
# Project created by QtCreator 2013-12-08T13:50:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TuringMachineEmulator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp\
        turingmachine.cpp\
        turinglent.cpp \
    newmachinedialog.cpp

HEADERS  += mainwindow.h\
        turingmachine.h\
        turinglent.h \
    newmachinedialog.h

FORMS    += mainwindow.ui \
    newmachinedialog.ui
