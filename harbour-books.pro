TEMPLATE = subdirs
CONFIG += ordered
SUBDIRS = bzip2 fribidi linebreak fbreader harbour-lib app

meta.files = META-INF
meta.path = /data/apps/com.syberos.fbreader

syber.files = sopconfig.xml
syber.path = /data/apps/com.syberos.fbreader

internalbook.files = books
internalbook.path = /data/apps/com.syberos.fbreader

INSTALLS += meta syber internalbook

OTHER_FILES += \
    README.md \
    rpm/harbour-books.spec
