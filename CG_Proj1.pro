#-------------------------------------------------
#
# Project created by QtCreator 2012-02-28T17:42:14
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = CG_Proj1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    opengl.cpp

HEADERS  += mainwindow.h \
    opengl.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    vshader.glsl \
    fshader.glsl

RESOURCES += \
    resources.qrc
