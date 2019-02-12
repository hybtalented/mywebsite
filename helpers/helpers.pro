TARGET = helper
TEMPLATE = lib
CONFIG += shared c++11
QT += xml qml sql network
QT -= gui 
DEFINES += TF_DLL
DESTDIR = ../lib
INCLUDEPATH += ../plugin
DEPENDPATH  +=
LIBS +=
MOC_DIR = .obj/
OBJECTS_DIR = .obj/

include(../appbase.pri)

HEADERS += applicationhelper.h
SOURCES += applicationhelper.cpp
HEADERS += elastic.h
SOURCES += elastic.cpp
HEADERS += config.h
SOURCES += config.cpp
HEADERS += sqlsynchelper.h
SOURCES += sqlsynchelper.cpp
