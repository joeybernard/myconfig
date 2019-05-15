include(../base.pri)
TEMPLATE = lib
QT      -= gui
QT      += network

DESTDIR  = $$SSNRX_LIBDIR

VERSION = 0.0.1

windows|wince*:!staticlib:!static:DEFINES += SSNRX_MAKEDLL

TARGET=ssnrx$$TARGET_SUFFIX

HEADERS += include/ssnrx.h \
    include/ssnrx_export.h \
    src/crc.h
SOURCES += src/ssnrx.cpp \
    src/crc.c

INCLUDEPATH += $$SSNRX_INCDIR
DEPENDPATH += $$QSERIALPORTDIR/include

# convenient way to use and link qserialport:
include($$QSERIALPORTDIR/qserialport.prf)
