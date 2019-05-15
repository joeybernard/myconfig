SDK_BASE = $$PWD
SSNRX_LIBDIR = $$SDK_BASE/bin
SSNRX_BINDIR = $$SDK_BASE/bin
SSNRX_INCDIR = $$SDK_BASE/ssnrx/include
QSERIALPORTDIR = $$SDK_BASE/qserialport
CONFIG(debug, debug|release) {
   TARGET_SUFFIX = "d"
}

QT += network
