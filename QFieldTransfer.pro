#-------------------------------------------------
#
# Project created by QtCreator 2013-01-10T00:14:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QFieldTransfer
TEMPLATE = app
QMAKE_CXXFLAGS += -std=gnu++11

SOURCES += main.cpp\
        mainwindow.cpp \
    field_transfer/VectorListPair.cpp \
    field_transfer/VectorList.cpp \
    field_transfer/Vector.cpp \
    field_transfer/Output.cpp \
    field_transfer/Number.cpp \
    field_transfer/Matrix.cpp \
    field_transfer/Index.cpp \
    field_transfer/Formula.cpp

HEADERS  += mainwindow.h \
    field_transfer/VectorListPair.h \
    field_transfer/VectorList.h \
    field_transfer/Vector.h \
    field_transfer/Output.h \
    field_transfer/Number.h \
    field_transfer/Matrix.h \
    field_transfer/main.h \
    field_transfer/Index.h \
    field_transfer/Formula.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    field_transfer/VectorListPair.mk \
    field_transfer/VectorList.mk \
    field_transfer/Vector.mk \
    field_transfer/Output.mk \
    field_transfer/Number.mk \
    field_transfer/Matrix.mk \
    field_transfer/main.mk \
    field_transfer/Index.mk \
    field_transfer/Formula.mk
