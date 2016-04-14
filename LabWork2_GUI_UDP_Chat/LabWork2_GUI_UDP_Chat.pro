#-------------------------------------------------
#
# Project created by QtCreator 2016-04-10T14:04:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LabWork2_GUI_UDP_Chat
TEMPLATE = app

CONFIG += c++11
CONFIG += c++14

INCLUDEPATH += /usr/local/include/boost/

LIBS += -L"/usr/local/lib/" -lboost_system -lpthread -lboost_regex -lboost_thread -lboost_exception -lboost_log

SOURCES += main.cpp \
    mainWindow.cpp

HEADERS  += \
    mainWindow.h \
    portValidator.h \
    IP_Validator.h \
    Libs.h \
    IncludedLibs.h \
    multicastUDPsocket.hpp \
    Peers.hpp \
    udpSocket.hpp \
    UsefulDataPacket.hpp

FORMS    += \
    mainWindow.ui
