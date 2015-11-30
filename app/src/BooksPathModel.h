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

#ifndef BOOKS_PATH_MODEL_H
#define BOOKS_PATH_MODEL_H

#include "BooksTypes.h"
#include "BooksStorage.h"

#include <QHash>
#include <QVariant>
#include <QByteArray>
#include <QAbstractListModel>
#include <QtQml>

class BooksPathModel: public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged)
    Q_PROPERTY(QObject* storage READ storage WRITE setStorage NOTIFY storageChanged)

public:
    explicit BooksPathModel(QObject* aParent = NULL);

    int count() const { return iList.count(); }
    QString path() const { return iPath; }
    void setPath(QString aPath);
    QObject* storage() { return &iStorage; }
    void setStorage(QObject* aStorage);

    // QAbstractListModel
    virtual QHash<int,QByteArray> roleNames() const;
    virtual int rowCount(const QModelIndex& aParent) const;
    virtual QVariant data(const QModelIndex& aIndex, int aRole) const;
    virtual bool setData(const QModelIndex& aIndex, const QVariant& aValue, int aRole);

Q_SIGNALS:
    void countChanged();
    void pathChanged();
    void storageChanged();

private:
    bool validIndex(int aIndex) const;

private:
    class Data {
    public:
        QString iParentPath;
        QString iPath;
        QString iName;
        Data(QString aParentPath, QString aPath, QString aName) :
            iParentPath(aParentPath), iPath(aPath), iName(aName) {}
    };

    BooksStorage iStorage;
    QList<Data> iList;
    QString iPath;
};

QML_DECLARE_TYPE(BooksPathModel)

inline bool BooksPathModel::validIndex(int aIndex) const
    { return aIndex >= 0 && aIndex < iList.count(); }

#endif // BOOKS_PATH_MODEL_H