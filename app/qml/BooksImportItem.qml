/*
  Copyright (C) 2015 Jolla Ltd.
  Contact: Slava Monich <slava.monich@jolla.com>

  You may use this file under the terms of BSD license as follows:

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions
  are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the Jolla Ltd nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS
  BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
  THE POSSIBILITY OF SUCH DAMAGE.
*/

import QtQuick 2.0
import com.syberos.basewidgets 2.0
import harbour.books 1.0
import "Theme.js" as Theme

Item {
    id: root
    width: parent.width
    height: contentHeight
    enabled: book ? true : false

    property var book
    property string _title: book ? book.title : ""
    property string _authors: book ? book.authors : ""

    signal clicked()

    BooksShelfItem {
        id: cover
        visible: root.enabled
        anchors {
            top: parent.top
            bottom: parent.bottom
            left: parent.left
            leftMargin: Theme.horizontalPageMargin
        }
        width: Math.round(height*3/4)
        book: root.book ? root.book : null
        name: _title
    }

    Column {
        visible: root.enabled
        anchors {
            left: cover.right
            leftMargin: Theme.paddingMedium
            right: parent.right
            rightMargin: Theme.horizontalPageMargin
            verticalCenter: parent.verticalCenter
        }
        CLabel {
            width: parent.width
            text: _authors
//            color: root.highlighted ? Theme.highlightColor : Theme.primaryColor
//            truncationMode: TruncationMode.Fade
//            font.pixelSize: Theme.fontSizeExtraSmall
        }
        CLabel {
            width: parent.width
            text: _title
//            color: root.highlighted ? Theme.highlightColor : Theme.primaryColor
//            truncationMode: TruncationMode.Fade
        }
    }

    Image {
        anchors {
            top: parent.top
            topMargin: Theme.paddingSmall
            right: parent.right
            rightMargin: Theme.paddingSmall
        }
        visible: highlighted
        source: "image://theme/icon-s-installed" + (highlighted ? "?" + Theme.highlightColor : "")
    }

    CIndicator {
        id: busyIndicator
        anchors.centerIn: parent
        visible: !root.enabled
//        running: visible
//        size: BusyIndicatorSize.Medium
        sizeMode: 0
    }

    MouseArea{
        anchors.fill: parent
        onClicked: clicked();
    }
}
