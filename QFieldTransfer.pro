#-------------------------------------------------
#
# Project created by QtCreator 2013-01-10T00:14:37
#
#-------------------------------------------------

CONFIG += qt
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QFieldTransfer
TEMPLATE = app
QMAKE_CXXFLAGS += -std=gnu++11 -O3
LIBS += -lboost_regex -lboost_system -lboost_thread

SOURCES += main.cpp\
        mainwindow.cpp \
    FieldTransfer/VectorListPair.cpp \
    FieldTransfer/VectorList.cpp \
    FieldTransfer/Vector.cpp \
    FieldTransfer/Output.cpp \
    FieldTransfer/Number.cpp \
    FieldTransfer/Matrix.cpp \
    FieldTransfer/FieldTransfer.cpp \
    FieldTransfer/Index.cpp \
    FieldTransfer/Formula.cpp \
    transferer.cpp

HEADERS  += mainwindow.h \
    FieldTransfer/VectorListPair.h \
    FieldTransfer/VectorList.h \
    FieldTransfer/Vector.h \
    FieldTransfer/Output.h \
    FieldTransfer/Number.h \
    FieldTransfer/Matrix.h \
    FieldTransfer/FieldTransfer.h \
    FieldTransfer/Index.h \
    FieldTransfer/Formula.h \
    transferer.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    FieldTransfer/VectorListPair.mk \
    FieldTransfer/VectorList.mk \
    FieldTransfer/Vector.mk \
    FieldTransfer/Output.mk \
    FieldTransfer/Number.mk \
    FieldTransfer/Matrix.mk \
    FieldTransfer/main.mk \
    FieldTransfer/Index.mk \
    FieldTransfer/Formula.mk

RESOURCES += \
    resource.qrc
