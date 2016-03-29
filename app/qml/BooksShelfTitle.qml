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

MouseArea {
    id: root
    implicitHeight: column.implicitHeight
    property alias text: label.text
    property bool currentFolder
    property bool editable
    property bool _highlighted: pressed
    property color _highlightedColor: Theme.rgba(Theme.highlightBackgroundColor, Theme.highlightBackgroundOpacity)
    property bool _showPress: !currentFolder && (_highlighted || pressTimer.running)

    signal rename(var to)
    signal startEdit()

    onEditableChanged: {
        // Sync edit field and the label
        if (editable) editor.text = text
    }

    Column {
        id: column
        width: parent.width
        spacing: 0

        Item {
            height: Theme.paddingSmall
            width: parent.width
        }

        Item {
            width: parent.width
            height: label.implicitHeight

            Image {
                id: icon
                height: label.height*3/4
                sourceSize.height: height
                fillMode: Image.PreserveAspectFit
                source: "images/folder.svg"
                anchors {
                    left: parent.left
                    leftMargin: Theme.paddingMedium
                    verticalCenter: parent.verticalCenter
                }
            }

            CLabel {
                id: label
//                truncationMode: TruncationMode.Fade
                anchors {
                    left: icon.right
                    leftMargin: Theme.paddingMedium
                    verticalCenter: parent.verticalCenter
                }
                onTextChanged: {
                    if (!editable) {
                        editor.text = text
                    }
                }
                color: (currentFolder || pressed) ? Theme.highlightColor : Theme.primaryColor
                visible: opacity > 0
                opacity: editable ? 0 : 1
//                Behavior on opacity { FadeAnimation {} }
                Behavior on color { ColorAnimation { duration: 100 } }
            }

            CTextField {
                id: editor
                width: parent.width - icon.width - 2*Theme.paddingMedium
                y: 0
                anchors {
                    left: icon.right
                    leftMargin: Theme.paddingMedium
                }
                textLeftMargin: 0
                textRightMargin: 0
//                textTopMargin: 0
                visible: opacity > 0
                opacity: editable ? 1 : 0
//                Behavior on opacity { FadeAnimation {} }
                //% "Enter folder name"
                placeholderText: qsTrId("shelf-title-placeholder")
//                EnterKey.enabled: text.length > 0 && text !== "." && text !== ".." && text.indexOf("/") < 0
//                EnterKey.onClicked: {
//                    if (editable) {
//                        if (text) {
//                            root.rename(text)
//                        }
//                        parent.focus = true
//                    }
//                }
            }
        }

        Item {
            height: Theme.paddingSmall
            width: parent.width
        }
    }

    onPressed: pressTimer.start()
    onCanceled: pressTimer.stop()

    onPressAndHold: {
        if (currentFolder && !editable) {
            root.startEdit()
            if (editable) {
                editor.forceActiveFocus()
            }
        }
    }

    Rectangle {
        anchors.fill: parent
        color: _showPress ? _highlightedColor : "transparent"
    }

    Timer {
        id: pressTimer
        interval: 50
    }
}
