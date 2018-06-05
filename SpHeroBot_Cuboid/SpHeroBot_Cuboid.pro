#-------------------------------------------------
#
# Project created by QtCreator 2018-05-15T23:00:37
#
#-------------------------------------------------

QT += 3dcore 3drender 3dinput 3dextras
QT += widgets
QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SpHeroBot
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    scenemodifier.cpp

HEADERS += \
        mainwindow.h \
    scenemodifier.h

FORMS += \
        mainwindow.ui
