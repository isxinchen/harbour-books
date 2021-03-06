/*
 * Copyright (C) 2004-2010 Geometer Plus <contact@geometerplus.com>
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

#ifndef __ZLUNIXFSMANAGER_H__
#define __ZLUNIXFSMANAGER_H__

#include "../../filesystem/ZLFSManager.h"
//#include <magic.h>

class ZLUnixFSManager : public ZLFSManager {

protected:
	ZLUnixFSManager();
	~ZLUnixFSManager();

	void normalizeRealPath(std::string &path) const;

private:
	std::string resolveSymlink(const std::string &path) const;
	ZLFSDir *createNewDirectory(const std::string &path) const;
	ZLFSDir *createPlainDirectory(const std::string &path) const;
	ZLInputStream *createPlainInputStream(const std::string &path) const;
	ZLOutputStream *createOutputStream(const std::string &path) const;
	bool removeFile(const std::string &path) const;
	std::string mimeType(const std::string &path) const;

	ZLFileInfo fileInfo(const std::string &path) const;

	int findArchiveFileNameDelimiter(const std::string &path) const;
	shared_ptr<ZLDir> rootDirectory() const;
	const std::string &rootDirectoryPath() const;
	std::string parentPath(const std::string &path) const;

	bool canRemoveFile(const std::string &path) const;

private:
//	magic_t myMagic;
};

#endif /* __ZLUNIXFSMANAGER_H__ */
