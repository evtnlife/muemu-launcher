#-------------------------------------------------
#
# Project created by QtCreator 2016-11-17T19:04:10
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MuTeeN
TEMPLATE = app

INCLUDEPATH += $$PWD/QtZip/zlib

unix {
    LIBS += -L$$PWD/QtZip/zlib -lz
}

win32 {
    LIBS += -L$$PWD/QtZip/zlib/Windows -lzdll
}

SOURCES += main.cpp\
        muteen.cpp \
    QtZip/zip.cpp \
    config.cpp \
    patchupdate.cpp \
    testversion.cpp

HEADERS  += muteen.h \
    QtZip/zconf.h \
    QtZip/zipreader.h \
    QtZip/zipwriter.h \
    QtZip/zlib.h \
    config.h \
    patchupdate.h \
    testversion.h \
    definitions.h \
    startgame.h

FORMS    += muteen.ui \
    config.ui

RESOURCES += \
    resource/resource.qrc

RC_FILE = resource/application.rc

