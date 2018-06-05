HEADERS       = glwidget.h \
                window.h \
                mainwindow.h \
                logo.h  \
                serial.h

SOURCES       = glwidget.cpp \
                main.cpp \
                window.cpp \
                mainwindow.cpp \
                logo.cpp \
                main.cpp \
                serial.cpp



QT = core
QT += widgets
QT += serialport

CONFIG += console
CONFIG -= app_bundle

TARGET = serial
TEMPLATE = app


# install
target.path = $$[QT_INSTALL_EXAMPLES]/opengl/hellogl2
INSTALLS += target