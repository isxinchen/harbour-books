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
    id: view

    property alias model: widget.model
    property alias page: widget.page
    property alias leftMargin: widget.leftMargin
    property alias rightMargin: widget.rightMargin
    property alias topMargin: widget.topMargin
    property alias bottomMargin: widget.bottomMargin
    property alias title: titleLabel.text
    property real leftSpaceReserved
    property real rightSpaceReserved
    property bool titleVisible
    property bool pageNumberVisible

    signal pageClicked()

    PageWidget {
        id: widget
        anchors.fill: parent
        topMargin: 20
        bottomMargin: 20
        settings: globalSettings
        model: bookModel
    }

    BooksTitleLabel {
        id: titleLabel
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
            topMargin: 10
            leftMargin: Math.max(view.leftMargin, leftSpaceReserved)
            rightMargin: Math.max(view.rightMargin, rightSpaceReserved)
        }
        centerX: Math.floor(view.width/2) - anchors.leftMargin
        height: Theme.itemSizeExtraSmall
        color: globalSettings.primaryPageToolColor
        opacity: titleVisible ? 1 : 0
    }

    CIndicator {
        anchors.centerIn: parent
        sizeMode: 0
        visible: widget.loading
        Behavior on opacity {}
    }

    CLabel {
        anchors {
            horizontalCenter: parent.horizontalCenter
            bottom: parent.bottom
            bottomMargin: 10
        }
        text: widget.page + 1
        height: Theme.itemSizeExtraSmall
        font.pixelSize: Theme.fontSizeSmall
        verticalAlignment: Text.AlignVCenter
        color: globalSettings.primaryPageToolColor
        opacity: pageNumberVisible ? 1 : 0
        visible: opacity > 0
        Behavior on opacity { FadeAnimation {} }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: view.pageClicked()
    }
}
