TEMPLATE = subdirs
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += ordered

SUBDIRS += src tests pythonwrapper

tests.depend = src
pythonwrapper.depend = src

OTHER_FILES += intercombinatorzor.py

HEADERS += \
    include/intercombinatorzor.h

OUT_PWD = $$shadowed($$PWD)

!equals(PWD, $${OUT_PWD}) {

    copydata.commands = cp $$PWD/intercombinatorzor.py $$OUT_PWD
    first.depends = $(first) copydata
    export(first.depends)
    export(copydata.commands)
    QMAKE_EXTRA_TARGETS += first copydata

}

