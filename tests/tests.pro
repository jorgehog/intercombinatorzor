TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

include(../defaults.pri)

LIBS += -L$$shadowed($$PWD)/../lib -licz_core

SOURCES += testsmain.cpp

INCLUDEPATH += ../include

OTHER_FILES += example.py


OUT_PWD = $$shadowed($$PWD)

!equals(PWD, $${OUT_PWD}) {

    copyscript.commands = cp $$PWD/example.py $$OUT_PWD
    first.depends = $(first) copyscript
    export(first.depends)
    export(copydata.commands)
    QMAKE_EXTRA_TARGETS += first copyscript

}
