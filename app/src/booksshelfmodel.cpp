#include <QDebug>

#include "BooksBook.h"
#include "booksshelfmodel.h"
#include "BooksItem.h"


enum BooksImportRole {
    BooksShelfRoleTitle = Qt::UserRole,
    BooksShelfRoleBook,
    BooksShelfRolePath
};

class BooksShelfModel::Data
{
public:
    QString title;
    QString path;
    BooksBook *booksBook;
};

BooksShelfModel::BooksShelfModel(QObject* aParent):
    QAbstractListModel(aParent)
{
    QDir dir("/home/user/books");
    QStringList pathList;

    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    dir.setSorting(QDir::Size | QDir::Reversed);

    QFileInfoList list = dir.entryInfoList();

    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        pathList.append(fileInfo.absoluteFilePath());
    }

    addBooks(pathList);

    beginResetModel();
    loadBooks();
    endResetModel();
}



BooksShelfModel::~BooksShelfModel()
{

}

void BooksShelfModel::loadBooks()
{
    mBookList.clear();

    for(int i = 0; i < mList.size(); i++){
        BooksShelfModel::Data *data = mList.at(i);
        delete data;
    }

    mList.clear();
    BooksDB::Instance().loadBooks(mBookList);

    for(BookList::iterator it = mBookList.begin(); it != mBookList.end(); it++){
        ZLFile file = (*it)->file();
        qDebug() << Q_FUNC_INFO
                 << "Load book title=" << QString::fromStdString((*it)->title())
                 << ",path=" << QString::fromStdString(file.path());

        BooksShelfModel::Data *data = new Data();
        BooksBook *booksBook = new BooksBook((*it));
        data->path = QString::fromStdString(file.path());
        data->title = QString::fromStdString((*it)->title());
        data->booksBook = booksBook;
        mList.append(data);
    }

    int size = mList.size();

    if(size < 9){
        for(int i = size; i < 9; i++){
            BooksShelfModel::Data *data = new Data();
            data->path = QString();
            data->title = QString();
            data->booksBook = NULL;
            mList.append(data);
        }
    }else if(size % 3 != 0){
        for(int i = size % 3; i < 3; i++){
            BooksShelfModel::Data *data = new Data();
            data->path = QString();
            data->title = QString();
            data->booksBook = NULL;
            mList.append(data);
        }
    }
}
QString BooksShelfModel::getPath(int index)
{
    qDebug() << Q_FUNC_INFO << "index=" << index;
    if(index >= 0 && index < mList.size()){
        return mList.at(index)->path;
    }
    return QString();
}

void BooksShelfModel::addBooks(QStringList filePaths)
{
    qDebug() << Q_FUNC_INFO << filePaths;
    for(int i = 0; i < filePaths.size(); i++){
        QString filePath = filePaths.at(i);
        const std::string path = filePath.toStdString();
        const shared_ptr<Book> book = Book::loadFromFile(ZLFile(path));
        if(book.isNull()){
            continue;
        }
        BooksDB::Instance().saveBook(book);
        BooksDB::Instance().saveBookStateStack(*book, myPositionStack);
    }
    refresh();
}
void BooksShelfModel::delBooks(QStringList filePaths)
{
    qDebug() << Q_FUNC_INFO << filePaths;
    for(int i = 0; i < filePaths.size(); i++){
        QString filePath = filePaths.at(i);


        for(BookList::iterator it = mBookList.begin(); it != mBookList.end(); it++){
            ZLFile file = (*it)->file();
            if(QString::fromStdString(file.path()) == filePath){
                bool ret = BooksDB::Instance().removeBook(*it);
                if(!ret){
                    qDebug() << Q_FUNC_INFO << "delete book failed";
                }
            }
        }
    }
    refresh();
}

void BooksShelfModel::refresh()
{
    beginResetModel();
    loadBooks();
    endResetModel();
}

QHash<int,QByteArray> BooksShelfModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles.insert(BooksShelfRoleTitle, "title");
    roles.insert(BooksShelfRoleBook, "book");
    roles.insert(BooksShelfRolePath, "path");
    return roles;
}

int BooksShelfModel::rowCount(const QModelIndex&) const
{
    return mList.count();
}



QVariant BooksShelfModel::data(const QModelIndex& aIndex, int aRole) const
{
    const int i = aIndex.row();
    if (i >= 0 && i < mList.count()) {
        BooksShelfModel::Data* data = mList.at(i);
        switch (aRole) {
        case BooksShelfRoleTitle: return QVariant(data->title);
        case BooksShelfRoleBook: return QVariant::fromValue(data->booksBook);
        case BooksShelfRolePath: return QVariant(data->path);
        }
    } else if (i == mList.count()) {
        switch (aRole) {
        case BooksShelfRoleTitle:
        case BooksShelfRolePath:return QString();
        case BooksShelfRoleBook: return QVariant::fromValue((QObject*)NULL);
        }
    }
    return QVariant();
}



