#-------------------------------------------------
#
# Project created by QtCreator 2015-12-31T14:20:49
#
#-------------------------------------------------

QT       += core gui
QT	 += xml
QT	 += xmlpatterns
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = T3project
TEMPLATE = app


SOURCES += main.cpp\
    t3engine.cpp \
    T3Engine/scene/scene.cpp \
    T3Engine/sprite/frame.cpp \
    T3Engine/manager/shadermanager.cpp \
    T3Engine/sprite/action.cpp \
    T3Engine/sprite/sprite.cpp \
    T3Engine/render/rendermodule.cpp \
    T3Engine/render/picture.cpp \
    T3Engine/manager/picturemanager.cpp \
    T3Engine/manager/spritemanager.cpp \
    T3Engine/entity/character/character.cpp \
    T3Engine/entity/entity.cpp

HEADERS  += \
    t3engine.h \
    T3Engine/scene/scene.h \
    T3Engine/sprite/frame.h \
    T3Engine/manager/shadermanager.h \
    T3Engine/sprite/action.h \
    T3Engine/sprite/sprite.h \
    T3Engine/render/rendermodule.h \
    T3Engine/render/picture.h \
    T3Engine/singleton.h \
    T3Engine/manager/picturemanager.h \
    T3Engine/manager/spritemanager.h \
    T3Engine/entity/character/character.h \
    T3Engine/entity/entity.h

RESOURCES += \
    shader.qrc
