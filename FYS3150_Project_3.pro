TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    vec3.cpp \
    solarsystem.cpp \
    celestialbody.cpp \
    euler.cpp \
    verlet.cpp

HEADERS += \
    vec3.h \
    solarsystem.h \
    celestialbody.h \
    euler.h \
    verlet.h
