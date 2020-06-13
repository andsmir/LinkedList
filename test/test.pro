QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase c++17 warn_on
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_linkedlisttest.cpp
INCLUDEPATH += ../ll_library
LIBS += -L../ll_library -lll_library
# Windows: LIBS += -L../../build-LinkedListVisualizer-Desktop_Qt_5_15_0_MinGW_32_bit-Debug/ll_library/debug -lll_library
