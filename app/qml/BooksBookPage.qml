import QtQuick 2.0
import com.syberos.basewidgets 2.0
import harbour.books 1.0
import "Theme.js" as Theme

CPage {

    BooksBookView {
        anchors.fill: parent
        opacity: book ? 1 : 0
        visible: opacity > 0
        book: globalSettings.currentBook ? globalSettings.currentBook : null
        onCloseBook: globalSettings.currentBook = null
        Behavior on opacity { FadeAnimation {} }
    }

    onStatusChanged: {
        if (status === CPageStatus.Show) {
            console.log("PlayingInterface: pagestauts is Show");
        }else if(status === CPageStatus.WillShow){
            console.log("PlayingInterface: pagestauts is WillShow");
            gScreenInfo.setWindowProperty("STATUSBAR_VISIBLE", false);
        }else if(status === CPageStatus.WillHide){
            console.log("PlayingInterface: pagestauts is WillHide");
            gScreenInfo.setWindowProperty("STATUSBAR_VISIBLE", true);
        }else if (status === CPageStatus.Hide) {
            console.log("PlayingInterface: pagestauts is Hide");
        }
    }
}
