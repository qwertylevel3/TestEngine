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

PRECOMPILED_HEADER = stable.h

INCLUDEPATH += $$PWD\T3Engine\entity\
INCLUDEPATH += $$PWD\T3Engine\entity\bullet\
INCLUDEPATH += $$PWD\T3Engine\entity\character\
INCLUDEPATH += $$PWD\T3Engine\entity\decoration\
INCLUDEPATH += $$PWD\T3Engine\entity\terrain
INCLUDEPATH += $$PWD\T3Engine\manager\
INCLUDEPATH += $$PWD\T3Engine\scene\
INCLUDEPATH += $$PWD\T3Engine\skill\
INCLUDEPATH += $$PWD\T3Engine\sprite\
INCLUDEPATH += $$PWD\T3Engine\

SOURCES += main.cpp\
    T3Engine/scene/scene.cpp \
    T3Engine/sprite/frame.cpp \
    T3Engine/manager/shadermanager.cpp \
    T3Engine/sprite/action.cpp \
    T3Engine/sprite/sprite.cpp \
    T3Engine/manager/picturemanager.cpp \
    T3Engine/manager/spritemanager.cpp \
    T3Engine/entity/character/character.cpp \
    T3Engine/entity/entity.cpp \
    T3Engine/gameconfigurator.cpp \
    T3Engine/t3engine.cpp \
    T3Engine/entity/decoration/decoration.cpp \
    T3Engine/entity/terrain/terrain.cpp \
    T3Engine/manager/charactermanager.cpp \
    T3Engine/manager/terrainmanager.cpp \
    T3Engine/manager/decorationmanager.cpp \
    T3Engine/inputmodule.cpp \
    T3Engine/skill/skill.cpp \
    T3Engine/skill/move.cpp \
    T3Engine/entity/bullet/bullet.cpp \
    T3Engine/manager/bulletmanager.cpp \
    T3Engine/skill/shoot.cpp \
    T3Engine/manager/scenemanager.cpp \
    T3Engine/orientation.cpp \
    T3Engine/sprite/picture.cpp \
    T3Engine/sprite/picturetext.cpp

HEADERS  += \
    T3Engine/scene/scene.h \
    T3Engine/sprite/frame.h \
    T3Engine/manager/shadermanager.h \
    T3Engine/sprite/action.h \
    T3Engine/sprite/sprite.h \
    T3Engine/singleton.h \
    T3Engine/manager/picturemanager.h \
    T3Engine/manager/spritemanager.h \
    T3Engine/entity/character/character.h \
    T3Engine/entity/entity.h \
    T3Engine/gameconfigurator.h \
    T3Engine/t3engine.h \
    T3Engine/entity/decoration/decoration.h \
    T3Engine/entity/terrain/terrain.h \
    T3Engine/manager/charactermanager.h \
    T3Engine/manager/terrainmanager.h \
    T3Engine/manager/decorationmanager.h \
    T3Engine/inputmodule.h \
    T3Engine/skill/skill.h \
    T3Engine/skill/move.h \
    T3Engine/entity/bullet/bullet.h \
    T3Engine/manager/bulletmanager.h \
    T3Engine/skill/shoot.h \
    T3Engine/manager/scenemanager.h \
    T3Engine/orientation.h \
    stable.h \
    T3Engine/sprite/picture.h \
    T3Engine/sprite/picturetext.h

RESOURCES += \
    shader.qrc
