#-------------------------------------------------
#
# Project created by QtCreator 2015-12-31T14:20:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = T3project
TEMPLATE = app


SOURCES += main.cpp\
    t3engine.cpp \
    T3Engine/scene/scene.cpp \
    T3Engine/sprite/picture.cpp \
    T3Engine/sprite/frame.cpp \
    T3Engine/manager/shadermanager.cpp \
    T3Engine/sprite/action.cpp

HEADERS  += \
    t3engine.h \
    T3Engine/scene/scene.h \
    T3Engine/sprite/picture.h \
    T3Engine/sprite/frame.h \
    T3Engine/manager/shadermanager.h \
    T3Engine/sprite/action.h \
    T3Engine/manager/singleton.h

RESOURCES += \
    shader.qrc
