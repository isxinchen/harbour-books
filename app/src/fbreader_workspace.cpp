#include "fbreader_workspace.h"
#include <QDebug>
#include <qpa/qplatformnativeinterface.h>


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
#include "booksshelfmodel.h"

#include "HarbourDebug.h"
#include "HarbourLib.h"

#include "ZLibrary.h"

#include <QProcess>

// If the current task is stuck for too long after being canceled it's
// probably stuck forever. Let "too long" be 10 seconds.
#if HARBOUR_DEBUG
   // But let it get stuck forever in debug build
#  define TASK_QUEUE_TIMEOUT (-1)
#else
   // There's no reason to wait forever in release build though.
#  define TASK_QUEUE_TIMEOUT (10000)
#endif

FBReader_Workspace::FBReader_Workspace(int argc, char **argv)
    : CWorkspace()
{
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
    BOOKS_QML_REGISTER(BooksShelfModel, "BooksShelfModel");
    HarbourLib::registerTypes(BOOKS_QML_PLUGIN,
        BOOKS_QML_PLUGIN_V1, BOOKS_QML_PLUGIN_V2);

    //拷贝内置书
    QString program = "/bin/cp";
    QStringList arguments;
    arguments << "/data/apps/com.syberos.fbreader/books" << "/home/user/" << "-R";

    QProcess *myProcess = new QProcess();
    myProcess->start(program, arguments);

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
//    QPlatformNativeInterface *native = QGuiApplication::platformNativeInterface();

//    native->setWindowProperty(m_view->handle(), "STATUSBAR_VISIBLE", false);
}

void FBReader_Workspace::onLaunchComplete(Option option, const QStringList& params)
{
    Q_UNUSED(params)

    switch (option) {
    case CWorkspace::HOME:
        qDebug()<< "Start by Home";
        break;
    case CWorkspace::URL:
        break;
    case CWorkspace::EVENT:
        break;
    case CWorkspace::DOCUMENT:
        break;
    default:
        break;
    }
}
