TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

include(../defaults.pri)

LIBS += -L$$shadowed($$PWD)/../lib -licz_core

SOURCES += testsmain.cpp

INCLUDEPATH += ../include

OTHER_FILES += example.py
