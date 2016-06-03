/*
 * Copyright (C) 2009-2010 Geometer Plus <contact@geometerplus.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

#include "../DBRunnables.h"
#include "../../../library/Book.h"
#include "../../sqldb/implsqlite/SQLiteFactory.h"

DeleteBookRunnable::DeleteBookRunnable(DBConnection &connection) {
	myFindFileId = new FindFileIdRunnable(connection);
	myDeleteFile = SQLiteFactory::createCommand(BooksDBQuery::DELETE_FILE, connection, "@file_id", DBValue::DBINT);
    //add by xinchen
    myDeleteStackPosition = SQLiteFactory::createCommand(BooksDBQuery::DELETE_STACK_POSITION, connection, "@book_id", DBValue::DBINT);
    myDeleteBookStateStack = SQLiteFactory::createCommand(BooksDBQuery::DELETE_BOOK_STATE_STACK, connection, "@book_id", DBValue::DBINT);
    myDeleteRecentBooks = SQLiteFactory::createCommand(BooksDBQuery::DELETE_RECENT_BOOKS, connection, "@book_id", DBValue::DBINT);
    myDeleteBookList = SQLiteFactory::createCommand(BooksDBQuery::DELETE_BOOK_LIST, connection, "@book_id", DBValue::DBINT);
    myDeleteNetFiles = SQLiteFactory::createCommand(BooksDBQuery::DELETE_NET_FILES, connection, "@file_id", DBValue::DBINT);
}

bool DeleteBookRunnable::run() {
	myFindFileId->setFileName(myFileName, true);
	if (!myFindFileId->run()) {
		return false;
	}

	(DBIntValue &) *myDeleteFile->parameter("@file_id").value() = myFindFileId->fileId();
    //add by xinchen
    if(!myBook.isNull()){
        ((DBIntValue&)*myDeleteStackPosition->parameter("@book_id").value()) = myBook->bookId();
        ((DBIntValue&)*myDeleteBookStateStack->parameter("@book_id").value()) = myBook->bookId();
        ((DBIntValue&)*myDeleteRecentBooks->parameter("@book_id").value()) = myBook->bookId();
        ((DBIntValue&)*myDeleteBookList->parameter("@book_id").value()) = myBook->bookId();
        ((DBIntValue&)*myDeleteNetFiles->parameter("@file_id").value()) = myFindFileId->fileId();
    }else{
        return false;
    }

    return myDeleteStackPosition->execute() &&
            myDeleteBookStateStack->execute() &&
            myDeleteRecentBooks->execute() &&
            myDeleteBookList->execute() &&
            myDeleteNetFiles->execute() &&
            myDeleteFile->execute();
}

void DeleteBookRunnable::setBook(shared_ptr<Book> book){
    myBook = book;
}
