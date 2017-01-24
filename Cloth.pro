#-------------------------------------------------
#
# Project created by QtCreator 2017-01-24T11:27:13
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Cloth
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mypanelopengl.cpp \
    shapes/cloth.cpp \
    shapes/sphere.cpp \
    shapes/tools/common.cpp \
    shapes/tools/ray.cpp \
    shapes/tools/spring.cpp \
    shapes/tools/vertex.cpp

HEADERS  += mainwindow.h \
    mypanelopengl.h \
    shapes/cloth.h \
    shapes/sphere.h \
    shapes/tools/common.h \
    shapes/tools/ray.h \
    shapes/tools/spring.h \
    shapes/tools/vertex.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc

LIBS += -lopengl32
