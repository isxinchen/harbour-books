//add by xinchen for new BooksShelf


import QtQuick 2.0
import com.syberos.basewidgets 2.0
import com.syberos.filemanager.filepicker 1.0
import harbour.books 1.0
import "Theme.js" as Theme

CPage {
    id: rootItem

    Rectangle {
        anchors.fill: parent
        color: "#BEBEBE"
    }

    BooksShelfModel{
        id: shelfModel
    }

    contentAreaItem:Item{

        anchors.fill: parent

        CEditGridView {
            id: grid

//            interactive: false
            anchors.fill: parent
            model: shelfModel
            cellWidth: 240
            cellHeight: (parent.height - 85) / 3

//            flickableDirection: Flickable.VerticalFlick

            header: Image {
                id: gridHeader
                width: parent.width
                height: 85
                source: "images/bookshelf_header_bg.png"

                MouseArea{
                    id: cancel
                    width: 100
                    height: 60
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 20
                    visible: grid.editing
                    enabled: grid.editing

                    Image{
                        anchors.fill: parent
                        source: !parent.pressed ? "images/button_normal.png" : "images/button_pressed.png"
                    }

                    Text {
                        anchors.fill: parent
                        color: "#444444"
                        font.bold: true
                        font.pixelSize: 25
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        text: qsTr("取消")

                    }

                    onClicked: {
                        grid.editing = false
                    }
                }

                Text {
                    text: "书 架"
                    anchors.centerIn: parent
                    font.pixelSize: 40
                    font.bold: true
                    color: "#3f3f3f"
                }

                MouseArea{
                    id: addBook
                    width: 100
                    height: 60
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    anchors.rightMargin: 20

                    Image{
                        anchors.fill: parent
                        source: !parent.pressed ? "images/button_normal.png" : "images/button_pressed.png"
                    }

                    Text {
                        anchors.fill: parent
                        color: "#444444"
                        font.bold: false
                        font.pixelSize: 25
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        text: grid.editing? qsTr("删除") : qsTr("添加")
                    }

                    onClicked: {
                        if(!grid.editing){
                            var index = -1;
                            switch(index){
                            case 0:
                                pageStack.push(filesPickerCom, {"category":3})
                                break;
                            case 1:
                                pageStack.push(filesPickerCom, {"category":1})
                                break;
                            case 2:
                                pageStack.push(filesPickerCom, {"category":2})
                                break;
                            case 3:
                            default:
                                pageStack.push(filesPickerCom)
                                break;
                            }
                        }else{

                            console.log("delete button is clicked..")

                            var selList = grid.selectedIndexes
                            var paths = []
                            console.log("delete button:" + selList + "   len="+selList.length)
                            for(var i = 0; i < selList.length; i++)
                            {
                                console.log("delete button:index=" + selList[i])
                                var path = shelfModel.getPath(selList[i])
                                paths.push(path)
                                console.log("delete button:path=" + path)
                            }
                            shelfModel.delBooks(paths);

                            grid.editing = false
                        }
                    }
                }
            }

            delegate: CEditGridViewDelegate{
                width: 240
                height: grid.cellHeight

                Image {
                    anchors.fill: parent
                    source: {
                        if (model.index % 3 == 0) {
                            return "images/bookshelf_layer_center1.png"
                        } else if (model.index % 3 == 1) {
                            return "images/bookshelf_layer_center2.png"
                        } else if (model.index % 3 == 2) {
                            return "images/bookshelf_layer_center3.png"
                        } else{
                            return "images/bookshelf_layer_center3.png"
                        }
                    }
                }

                BookCover{
                    width: 220
                    height: 220*6/5
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 25
                    book: model.book ? model.book : null
                    visible: model.book

                    BooksTitleText {
                        id: title
                        anchors.centerIn: parent
                        width: parent.width - 2 * Theme.paddingMedium
                        height: parent.height - 2 * Theme.paddingMedium
                        text: model.title
                        visible: parent.empty
                    }
                }

                onClicked: {
                    if(model.book){
                        globalSettings.currentBook = model.book
                        gAppUtils.pageStackWindow.pageStack.push(Qt.resolvedUrl("BooksBookPage.qml"));
                    }
                }
            }
            property real itemOpacity: 1
//            property real minContentY: -headerItem.height

            moveDisplaced: Transition {
                SmoothedAnimation { properties: "x,y"; duration: 150 }
            }

            removeDisplaced: Transition {
                SmoothedAnimation { properties: "x,y"; duration: 150 }
            }

//            NumberAnimation {
//                id: fadeAnimation
//                target: grid
//                property: "itemOpacity"
//                from: 1
//                to: 0
//                duration: _remorseTimeout
//                easing.type: Easing.OutCubic
//            }

            onActiveFocusChanged: console.log("BooksShelfView.grid", activeFocus)

            Behavior on y { SpringAnimation {} }
    //        VerticalScrollDecorator {}
        }

//        BooksDragArea {
//            id: dragArea
////            dragParent: storageView
//            gridView: grid
//            onDeleteItemAt: {
//                if (!shelfView.deleteAllRequest) {
//                    shelfView.shelf.setDeleteRequested(index, true);
//                }
//            }
//            onDropItem: shelfView.dropItem(mouseX, mouseY)
//            onActiveFocusChanged: console.log("BooksShelfView.grid.dragArea", activeFocus)
//            Component.onCompleted: {
//                console.log("BooksDragArea created")
//                grid.focus = true
//            }
//        }
    }

    // file list for select attach
       Component{
           id: filesPickerCom
           SyberosFilesPicker{
               id: filesPicker
               onOk:{
                   var selectedSize = filesPicker.getFileSize()
                   console.log("selectedSize=" + selectedSize.length)

                   shelfModel.addBooks(filesPicker.filesPath)
//                   var size = 0;
//                   var selectedSize = filesPicker.getFileSize()
//                   for(var i = 0; i < selectedSize.length; i++){
//                       size += parseInt(selectedSize[i])
//                   }

//                   // check disk space
//                   var freeSpace = emailHandler.diskFreeSpace() //内置sd卡剩余空间
//                   if(size + allAttachSize > freeSpace){
//                       gToast.requestToast(os.i18n.ctr(qsTr("The storage space is insufficient, cannot add the attachment")))
//                       return
//                   }

//                   if(size + allAttachSize > maxAttachSize){
//                       gToast.requestToast(os.i18n.ctr(qsTr("Total file size can not exceed 10M, add attachments failed")))
//                       return
//                   }
//                   for(var j = 0; j < filesPicker.filesPath.length; j++){
//                       attach.append(filesPicker.filesPath[j], parseInt(selectedSize[j]))
//                   }
//                   allAttachSize += size;
//                   if((!attach.visible) && filesPicker.filesPath.length > 0) {
//                       attach.visible = true
//                       attach.adjustArrowRotation()
//                   }
//                   window.clearFocus()
               }
           }
       }
}
