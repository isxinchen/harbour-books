/*
 * Copyright (C) 2015 Jolla Ltd.
 * Contact: Slava Monich <slava.monich@jolla.com>
 *
 * You may use this file under the terms of the BSD license as follows:
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the documentation and/or other materials provided with the
 *     distribution.
 *   * Neither the name of Nemo Mobile nor the names of its contributors
 *     may be used to endorse or promote products derived from this
 *     software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "BooksDefs.h"
#include "BooksShelf.h"
#include "BooksBook.h"
#include "BooksBookModel.h"
#include "BooksCoverModel.h"
#include "BooksConfig.h"
#include "BooksSettings.h"
#include "BooksImportModel.h"
#include "BooksPathModel.h"
#include "BooksStorageModel.h"
#include "BooksPageWidget.h"
#include "BooksListWatcher.h"
#include "BooksCoverWidget.h"
#include "BooksTaskQueue.h"
#include "BooksHints.h"

#include "HarbourDebug.h"
#include "HarbourLib.h"

#include "ZLibrary.h"

//#include <sailfishapp.h>

#include <QGuiApplication>

// If the current task is stuck for too long after being canceled it's
// probably stuck forever. Let "too long" be 10 seconds.
#if HARBOUR_DEBUG
   // But let it get stuck forever in debug build
#  define TASK_QUEUE_TIMEOUT (-1)
#else
   // There's no reason to wait forever in release build though.
#  define TASK_QUEUE_TIMEOUT (10000)
#endif

Q_DECL_EXPORT int main(int argc, char **argv)
{
//    QGuiApplication* app = SailfishApp::application(argc, argv);
    QGuiApplication* app = new QGuiApplication(argc, argv);
    BOOKS_QML_REGISTER(BooksShelf, "Shelf");
    BOOKS_QML_REGISTER(BooksBook, "Book");
    BOOKS_QML_REGISTER(BooksBookModel, "BookModel");
    BOOKS_QML_REGISTER(BooksCoverModel, "CoverModel");
    BOOKS_QML_REGISTER(BooksImportModel, "BooksImportModel");
    BOOKS_QML_REGISTER(BooksPathModel, "BooksPathModel");
    BOOKS_QML_REGISTER(BooksStorageModel, "BookStorage");
    BOOKS_QML_REGISTER(BooksPageWidget, "PageWidget");
    BOOKS_QML_REGISTER(BooksListWatcher, "ListWatcher");
    BOOKS_QML_REGISTER(BooksCoverWidget, "BookCover");
    BOOKS_QML_REGISTER(BooksSettings, "BooksSettings");
    BOOKS_QML_REGISTER(BooksHints, "BooksHints");
    HarbourLib::registerTypes(BOOKS_QML_PLUGIN,
        BOOKS_QML_PLUGIN_V1, BOOKS_QML_PLUGIN_V2);

//    QLocale locale;
//    QTranslator* translator = new QTranslator(app);
//    QString transDir = SailfishApp::pathTo("translations").toLocalFile();
//    QString transFile(BOOKS_APP_NAME);
//    if (translator->load(locale, transFile, "-", transDir) ||
//        translator->load(transFile, transDir)) {
//        app->installTranslator(translator);
//    } else {
//        HDEBUG("Failed to load translator for" << locale);
//        delete translator;
//    }

    BooksConfigManager configManager;
    if (ZLibrary::init(argc, argv)) {
        ZLibrary::run(NULL);
        BooksTaskQueue::waitForDone(TASK_QUEUE_TIMEOUT);
        ZLibrary::shutdown();
    }

    delete app;
    return 0;
}
