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

#include "BooksTextView.h"
#include "BooksTextStyle.h"

#include "ZLStringUtil.h"

#define SUPER ZLTextView

const ZLColor BooksTextView::DEFAULT_BACKGROUND(238, 238, 238);
const ZLColor BooksTextView::INVERTED_BACKGROUND(65, 67, 95);

BooksTextView::BooksTextView(
    BooksPaintContext& aContext,
    shared_ptr<ZLTextStyle> aTextStyle,
    BooksMargins aMargins) :
    SUPER(aContext),
    iMargins(aMargins),
    iPaintContext(aContext),
    iTextStyle(aTextStyle),
    isInvertColors(false)
{
}

void BooksTextView::paint()
{
    SUPER::paint();
}

const std::string& BooksTextView::caption() const
{
    return iCaption;
}

int BooksTextView::leftMargin() const
{
    return iMargins.iLeft + iTextStyle->fontSize();
}

int BooksTextView::rightMargin() const
{
    return iMargins.iRight + iTextStyle->fontSize();
}

int BooksTextView::topMargin() const
{
    return iMargins.iTop;
}

int BooksTextView::bottomMargin() const
{
    return iMargins.iBottom;
}

bool BooksTextView::stylusPress(int x, int y)
{
    onStylusPress(x, y);
}
bool BooksTextView::stylusRelease(int x, int y)
{
    onStylusRelease(x, y);
}
bool BooksTextView::stylusMove(int x, int y)
{
    onStylusMove(x, y);
}
bool BooksTextView::stylusMovePressed(int x, int y)
{
    onStylusPress(x, y);
}
bool BooksTextView::fingerTap(int x, int y)
{
    onFingerTap(x, y);
}

ZLColor BooksTextView::backgroundColor() const
{
    if(isInvertColors){
        QColor color = qtColor(INVERTED_BACKGROUND);
        return ZLColor(color.red(), color.green(), color.blue());
    }else{
        QColor color = qtColor(DEFAULT_BACKGROUND);
        return ZLColor(color.red(), color.green(), color.blue());
    }
//    return iPaintContext.realColor(INVERTED_BACKGROUND);
}

ZLColor BooksTextView::color(const std::string &aStyle) const
{
    static const std::string INTERNAL_HYPERLINK("internal");
    static const std::string EXTERNAL_HYPERLINK("external");
    static const std::string BOOK_HYPERLINK("book");

    if (ZLStringUtil::startsWith(aStyle, '#')) {
        if (aStyle.length() == 7) {
            int i, value = 0;
            for (i=1; i<7; i++) {
                int nibble = ZLStringUtil::fromHex(aStyle[i]);
                if (nibble >= 0) {
                    value <<= 4;
                    value |= nibble;
                } else {
                    break;
                }
            }
            if (i == 7) {
                return iPaintContext.realColor(ZLColor(value));
            }
        }
    } else if (aStyle == INTERNAL_HYPERLINK) {
        return iPaintContext.realColor(33, 96, 180);
    } else if (aStyle == EXTERNAL_HYPERLINK) {
        return iPaintContext.realColor(33, 96, 180);
    } else if (aStyle == BOOK_HYPERLINK) {
        return iPaintContext.realColor(23, 68, 128);
    } else if (aStyle == ZLTextStyle::SELECTION_BACKGROUND) {
        return iPaintContext.realColor(82, 131, 194);
    } else if (aStyle == ZLTextStyle::HIGHLIGHTED_TEXT) {
        return iPaintContext.realColor(60, 139, 255);
    }

    if(isInvertColors){
        return ZLColor(117, 130, 154);
    }else{
        return ZLColor(68, 68, 68);
    }

    return iPaintContext.realColor(68, 68, 68);//"#404040"
}

shared_ptr<ZLTextStyle> BooksTextView::baseStyle() const
{
    return iTextStyle;
}

bool BooksTextView::isSelectionEnabled() const
{
    return false;
}

int BooksTextView::doubleClickDelay() const
{
    return isSelectionEnabled() ? 200 : 0;
}

shared_ptr<ZLTextPositionIndicatorInfo> BooksTextView::indicatorInfo() const
{
    return NULL;
}

const BooksPos BooksTextView::rewind()
{
    SUPER::gotoPosition(0, 0, 0);
    preparePaintInfo();
    if (!textArea().isVisible()) nextPage();
    return position();
}

bool BooksTextView::nextPage()
{
    BooksPos saved(position());
    BooksPos current(saved);
    do {
        scrollPage(true, ZLTextAreaController::NO_OVERLAPPING, 1);
        preparePaintInfo();
        const BooksPos pos = position();
        if (pos == current) {
            gotoPosition(saved);
            return false;
        }
        current = pos;
    } while (!textArea().isVisible());
    return true;
}

void BooksTextView::gotoPosition(const BooksPos& aPos)
{
    SUPER::gotoPosition(aPos.iParagraphIndex, aPos.iElementIndex,
        aPos.iCharIndex);
}
