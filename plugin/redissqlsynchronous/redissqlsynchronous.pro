TARGET = RDSSync
TEMPLATE = lib
CONFIG += plugin
DESTDIR = ../lib
INCLUDEPATH += ../../helpers
LIBS += -L../../lib -lhelper
include(../../appbase.pri)
HEADERS = RDSSync.h 
SOURCES = RDSSync.cpp 
HEADERS += ../syncplugin.h
QT += network  sql
QT -= gui
DEFINES += TF_DLL
DEPENDPATH  += ../../helpers
INCLUDEPATH  += ../../helpers
CONFIG += shared c++11