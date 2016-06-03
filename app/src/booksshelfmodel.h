#ifndef BOOKSSHELFMODEL_H
#define BOOKSSHELFMODEL_H

#include <QAbstractListModel>

#include "fbreader/ReadingState.h"

#include "database/booksdb/BooksDB.h"
#include "library/Book.h"

class BooksShelfModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit BooksShelfModel(QObject* aParent = NULL);
    ~BooksShelfModel();

    Q_INVOKABLE QString getPath(int index);
    Q_INVOKABLE void addBooks(QStringList filePaths);
    Q_INVOKABLE void delBooks(QStringList filePaths);
    Q_INVOKABLE void refresh();

    virtual QHash<int,QByteArray> roleNames() const;
    virtual int rowCount(const QModelIndex& aParent) const;
    virtual QVariant data(const QModelIndex& aIndex, int aRole) const;
private:
    void loadBooks();

private:
    class Data;
    typedef ReadingState Position;
    typedef std::deque<Position> PositionStack;
    PositionStack myPositionStack;
    QList<Data*> mList;
    BookList mBookList;
};

#endif // BOOKSSHELFMODEL_H
