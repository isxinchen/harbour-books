TEMPLATE = lib
TARGET = bzip2
CONFIG += staticlib link_pkgconfig
PKGCONFIG += glib-2.0

!include(../common.pri)

SRC_DIR = bzip2

INCLUDEPATH += $$SRC_DIR

DEFINES += USE_SIMPLE_MALLOC=1

HEADERS += \
    $$SRC_DIR/bzlib.h \
    $$SRC_DIR/bzlib_private.h

SOURCES += \
    $$SRC_DIR/blocksort.c \
    $$SRC_DIR/bzip2.c \
    $$SRC_DIR/bzip2recover.c \
    $$SRC_DIR/bzlib.c \
    $$SRC_DIR/compress.c \
    $$SRC_DIR/crctable.c \
    $$SRC_DIR/decompress.c \
    $$SRC_DIR/dlltest.c \
    $$SRC_DIR/huffman.c \
    $$SRC_DIR/mk251.c \
    $$SRC_DIR/randtable.c \
    $$SRC_DIR/spewG.c \
    $$SRC_DIR/unzcrash.c
