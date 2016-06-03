TARGET = fbreader
CONFIG += link_pkgconfig
PKGCONFIG += mlite5 glib-2.0

PKGCONFIG += syberos-application syberos-application-cache

#QT += dbus

QT += qml quick gui-private

!include(../common.pri)

CONFIG(debug, debug|release) {
  DEFINES += HARBOUR_DEBUG=1
}

# Directories
FBREADER_DIR = $$_PRO_FILE_PWD_/../fbreader
FRIBIDI_DIR = $$_PRO_FILE_PWD_/../fribidi
LINEBREAK_DIR = $$_PRO_FILE_PWD_/../linebreak
HARBOUR_LIB_DIR = $$_PRO_FILE_PWD_/../harbour-lib
BZIP2_DIR = $$_PRO_FILE_PWD_/../bzip2

# Libraries
FBREADER_LIB = $$OUT_PWD/../fbreader/libfbreader.a
FRIBIDI_LIB = $$OUT_PWD/../fribidi/libfribidi.a
LINEBREAK_LIB = $$OUT_PWD/../linebreak/liblinebreak.a
HARBOUR_LIB = $$OUT_PWD/../harbour-lib/libharbour-lib.a
BZIP2_LIB = $$OUT_PWD/../bzip2/libbzip2.a

PRE_TARGETDEPS += \
  $$FBREADER_LIB \
  $$FRIBIDI_LIB \
  $$LINEBREAK_LIB \
  $$HARBOUR_LIB \
  $$BZIP2_LIB
LIBS += \
  $$FBREADER_LIB \
  $$FRIBIDI_LIB \
  $$LINEBREAK_LIB \
  $$HARBOUR_LIB \
  $$BZIP2_LIB \
  -lz -ldl -lexpat -ludev -lsqlite3

OTHER_FILES += \
  icons/harbour-books.svg \
  harbour-books.desktop \
  qml/*.qml \
  qml/images/* \
  data/default/* \
  data/zlibrary/core/encodings/* \
  data/zlibrary/core/resources/* \
  translations/*.ts

#TARGET_DATA_DIR = /usr/share/harbour-books
#TARGET_DEFAULT_DATA_DIR = $$TARGET_DATA_DIR/data
#TARGET_ZLIBRARY_DATA_DIR = $$TARGET_DEFAULT_DATA_DIR
#TARGET_ICON_ROOT = /usr/share/icons/hicolor

TARGET_DATA_DIR = /data/apps/com.syberos.fbreader
TARGET_DEFAULT_DATA_DIR = $$TARGET_DATA_DIR/data
TARGET_ZLIBRARY_DATA_DIR = $$TARGET_DEFAULT_DATA_DIR
TARGET_ICON_ROOT = $$TARGET_DATA_DIR/icons/hicolor

qml_dir.files = qml
qml_dir.path = $$TARGET_DATA_DIR/

target.path = $$TARGET_DATA_DIR/bin

covers.files = qml/images/covers
covers.path = $$TARGET_ZLIBRARY_DATA_DIR

default_icon.files = icons/logo.png
default_icon.path = $$TARGET_DATA_DIR/icons

INSTALLS += target qml_dir covers default_icon

core_data.files = \
  data/zlibrary/core/*.gz \
  data/zlibrary/core/*.zip \
  data/zlibrary/core/encodings \
  data/zlibrary/core/resources
core_data.path = $$TARGET_ZLIBRARY_DATA_DIR
INSTALLS += core_data

text_data.files = data/zlibrary/text/*.zip
text_data.path = $$TARGET_ZLIBRARY_DATA_DIR
INSTALLS += text_data

defaults.files = data/default/*
defaults.path = $$TARGET_ZLIBRARY_DATA_DIR
INSTALLS += defaults

formats.files = data/formats/*
formats.path = $$TARGET_DEFAULT_DATA_DIR/formats
INSTALLS += formats

icon86.files = icons/86x86/harbour-books.png
icon86.path = $$TARGET_ICON_ROOT/86x86/apps
INSTALLS += icon86

icon108.files = icons/108x108/harbour-books.png
icon108.path = $$TARGET_ICON_ROOT/108x108/apps
INSTALLS += icon108

icon128.files = icons/128x128/harbour-books.png
icon128.path = $$TARGET_ICON_ROOT/128x128/apps
INSTALLS += icon128

icon256.files = icons/256x256/harbour-books.png
icon256.path = $$TARGET_ICON_ROOT/256x256/apps
INSTALLS += icon256

CONFIG += sailfishapp_i18n sailfishapp_i18n_idbased
TRANSLATIONS += \
    translations/harbour-books.ts \
    translations/harbour-books-fi.ts \
    translations/harbour-books-ru.ts \
    translations/harbour-books-sv.ts

INCLUDEPATH += \
  src \
  $$HARBOUR_LIB_DIR/include \
  $$FBREADER_DIR/fbreader/fbreader/src \
  $$FBREADER_DIR/fbreader/zlibrary/text/include \
  $$FBREADER_DIR/fbreader/zlibrary/core/include \
  $$FBREADER_DIR/fbreader/zlibrary/core/src/view \
  $$FBREADER_DIR/fbreader/zlibrary/core/src/dialogs \
  $$FBREADER_DIR/fbreader/zlibrary/core/src/application \
  $$FBREADER_DIR/fbreader/zlibrary/core/src/options \
  $$FBREADER_DIR/fbreader/zlibrary/core/src/unix \
  $$FBREADER_DIR/fbreader/zlibrary/ui/src/qt4

SOURCES += \
  src/MGConfItem.cpp \
  src/BooksBook.cpp \
  src/BooksBookModel.cpp \
  src/BooksConfig.cpp \
  src/BooksCoverModel.cpp \
  src/BooksCoverWidget.cpp \
  src/BooksDialogManager.cpp \
  src/BooksHints.cpp \
  src/BooksImportModel.cpp \
  src/BooksListWatcher.cpp \
  src/BooksLoadingProperty.cpp \
  src/BooksPageWidget.cpp \
  src/BooksPaintContext.cpp \
  src/BooksPathModel.cpp \
  src/BooksSaveTimer.cpp \
  src/BooksSettings.cpp \
  src/BooksShelf.cpp \
  src/BooksStorage.cpp \
  src/BooksStorageModel.cpp \
  src/BooksTask.cpp \
  src/BooksTextStyle.cpp \
  src/BooksTaskQueue.cpp \
  src/BooksTextView.cpp \
  src/BooksUtil.cpp \
  src/main.cpp \
  src/ZLApplication.cpp \
  src/ZLibrary.cpp \
    src/fbreader_workspace.cpp \
    src/booksshelfmodel.cpp


# Stubs for the libraries not allowed in harbour
#SOURCES += \
#  stubs/libexpat.c
#  stubs/libmagic.c \
#  stubs/libudev.c


HEADERS += \
  src/BooksBook.h \
  src/BooksBookModel.h \
  src/BooksConfig.h \
  src/BooksCoverModel.h \
  src/BooksCoverWidget.h \
  src/BooksDefs.h \
  src/BooksDialogManager.h \
  src/BooksHints.h \
  src/BooksImportModel.h \
  src/BooksItem.h \
  src/BooksListWatcher.h \
  src/BooksLoadingProperty.h \
  src/BooksPageWidget.h \
  src/BooksPaintContext.h \
  src/BooksPathModel.h \
  src/BooksPos.h \
  src/BooksSaveTimer.h \
  src/BooksSettings.h \
  src/BooksShelf.h \
  src/BooksStorage.h \
  src/BooksStorageModel.h \
  src/BooksTask.h \
  src/BooksTaskQueue.h \
  src/BooksTextView.h \
  src/BooksTextStyle.h \
  src/BooksTypes.h \
  src/BooksUtil.h \
    src/MGConfItem.h \
    src/fbreader_workspace.h \
    src/booksshelfmodel.h \
    src/debug.h
