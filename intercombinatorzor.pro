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
