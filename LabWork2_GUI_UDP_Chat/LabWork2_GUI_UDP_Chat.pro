#-------------------------------------------------
#
# Project created by QtCreator 2016-04-10T14:04:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LabWork2_GUI_UDP_Chat
TEMPLATE = app


SOURCES += main.cpp \
    mainWindow.cpp

HEADERS  += \
    mainWindow.h \
    portValidator.h \
    IP_Validator.h \
    Libs.h

FORMS    += \
    mainWindow.ui
