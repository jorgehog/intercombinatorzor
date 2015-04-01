TEMPLATE = lib

TARGET = ../lib/icz_core

include(../defaults.pri)

SOURCES += \
    combine.cpp

HEADERS += \
    combine.h

LIBS += -fopenmp


QMAKE_PRE_LINK += $(MKDIR) $$PWD/../lib $$shadowed($$PWD)/../lib


