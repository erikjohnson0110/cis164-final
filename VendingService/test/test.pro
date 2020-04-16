QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_inventorytests.cpp \
    ../src/item.cpp \
    ../src/inventory.cpp \
    ../src/item.h \
    ../src/inventory.h
INCLUDEPATH += ../src
