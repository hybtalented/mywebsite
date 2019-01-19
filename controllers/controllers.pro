TARGET = controller
TEMPLATE = lib
CONFIG += shared c++11
QT += network sql xml qml
QT -= gui
DEFINES += TF_DLL
DESTDIR = ../lib
INCLUDEPATH += ../helpers ../models
DEPENDPATH  += ../helpers ../models
LIBS += -L../lib -lhelper -lmodel
MOC_DIR = .obj/
OBJECTS_DIR = .obj/

include(../appbase.pri)

HEADERS += applicationcontroller.h
SOURCES += applicationcontroller.cpp
HEADERS += blogcontroller.h
SOURCES += blogcontroller.cpp
HEADERS += usercontroller.h
SOURCES += usercontroller.cpp
HEADERS += jstoolscontroller.h
SOURCES += jstoolscontroller.cpp
HEADERS += informationmailer.h
SOURCES += informationmailer.cpp
