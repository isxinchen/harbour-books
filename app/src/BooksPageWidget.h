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

#ifndef BOOKS_PAGE_WIDGET_H
#define BOOKS_PAGE_WIDGET_H

#include "BooksTypes.h"
#include "BooksTask.h"
#include "BooksTaskQueue.h"
#include "BooksSettings.h"
#include "BooksBookModel.h"
#include "BooksPos.h"
#include "BooksPaintContext.h"
#include "BooksLoadingProperty.h"

#include "ZLTextStyle.h"

#include <QQuickPaintedItem>
#include <QTimer>

class BooksPageWidget: public QQuickPaintedItem, private BooksLoadingProperty
{
    Q_OBJECT
    Q_PROPERTY(bool loading READ loading NOTIFY loadingChanged)
    Q_PROPERTY(int page READ page WRITE setPage NOTIFY pageChanged)
    Q_PROPERTY(int leftMargin READ leftMargin WRITE setLeftMargin NOTIFY leftMarginChanged)
    Q_PROPERTY(int rightMargin READ rightMargin WRITE setRightMargin NOTIFY rightMarginChanged)
    Q_PROPERTY(int topMargin READ topMargin WRITE setTopMargin NOTIFY topMarginChanged)
    Q_PROPERTY(int bottomMargin READ bottomMargin WRITE setBottomMargin NOTIFY bottomMarginChanged)
    Q_PROPERTY(BooksBookModel* model READ model WRITE setModel NOTIFY modelChanged)
    Q_PROPERTY(BooksSettings* settings READ settings WRITE setSettings NOTIFY settingsChanged)

public:
    class Data;

    BooksPageWidget(QQuickItem* aParent = NULL);
    ~BooksPageWidget();

    bool loading() const;

    int page() const { return iPage; }
    void setPage(int aPage);

    BooksBookModel* model() const { return iModel; }
    void setModel(BooksBookModel* aModel);

    BooksSettings* settings() const { return iSettings; }
    void setSettings(BooksSettings* aSettings);

    int leftMargin() const { return iMargins.iLeft; }
    int rightMargin() const { return iMargins.iRight; }
    int topMargin() const { return iMargins.iTop; }
    int bottomMargin() const { return iMargins.iBottom; }

    void setLeftMargin(int aMargin);
    void setRightMargin(int aMargin);
    void setTopMargin(int aMargin);
    void setBottomMargin(int aMargin);

    BooksMargins margins() const { return iMargins; }

    Q_INVOKABLE bool onStylusPress(int x, int y);
    Q_INVOKABLE bool onStylusRelease(int x, int y);
    Q_INVOKABLE bool onStylusMove(int x, int y);
    Q_INVOKABLE bool onStylusMovePressed(int x, int y);
    Q_INVOKABLE bool onFingerTap(int x, int y);

Q_SIGNALS:
    void loadingChanged();
    void pageChanged();
    void modelChanged();
    void settingsChanged();
    void leftMarginChanged();
    void rightMarginChanged();
    void topMarginChanged();
    void bottomMarginChanged();

private Q_SLOTS:
    void onWidthChanged();
    void onHeightChanged();
    void onResizeTimeout();
    void onBookModelChanged();
    void onBookModelDestroyed();
    void onBookModelPageMarksChanged();
    void onBookModelLoadingChanged();
    void onTextStyleChanged();
    void onInvertColorsChanged();
    void onResetTaskDone();
    void onRenderTaskDone();

private:
    void paint(QPainter *painter);
    void updateSize();
    void resetView();
    void scheduleRepaint();
    void cancelRepaint();
    bool invertColors() const;

private:
    class ResetTask;
    class RenderTask;

    shared_ptr<BooksTaskQueue> iTaskQueue;
    shared_ptr<ZLTextStyle> iTextStyle;
    BooksPos iPageMark;
    QTimer* iResizeTimer;
    BooksBookModel* iModel;
    BooksSettings* iSettings;
    BooksMargins iMargins;
    shared_ptr<Data> iData;
    shared_ptr<QImage> iImage;
    ResetTask* iResetTask;
    RenderTask* iRenderTask;
    bool iEmpty;
    int iPage;
};

inline bool BooksPageWidget::invertColors() const
    { return iSettings && iSettings->invertColors(); }

#endif // BOOKS_PAGE_WIDGET_H
