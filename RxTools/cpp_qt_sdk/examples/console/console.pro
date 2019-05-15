include(../../base.pri)

CONFIG += console
DESTDIR  = $$SSNRX_BINDIR

HEADERS += \
    consoleprintingclient.h \
    consolewindow.h
SOURCES += \
    consoleprintingclient.cpp \
    main.cpp \
    consolewindow.cpp

INCLUDEPATH += \
    $$SSNRX_INCDIR
DEPENDPATH += $$QSERIALPORTDIR/include \
    $$SSNRX_INCDIR

win32:LIBS += -lssnrx$${TARGET_SUFFIX}0 -L$$SSNRX_LIBDIR
unix:LIBS += -lssnrx$${TARGET_SUFFIX} -L$$SSNRX_LIBDIR

# convenient way to use and link qserialport:
include($$QSERIALPORTDIR/qserialport.prf)
