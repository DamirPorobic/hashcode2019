/*
 * Copyright (C) 2019 Damir Porobic <damir.porobic@gmx.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "FileParser.h"
#include "TagStorage.h"

list<Photo> FileParser::parse(const string &filename, TagStorage &tagStorage) const
{
	ifstream infile(filename);
	string line;
	int photoId = 0;
	getline(infile, line); // remove first line, we don't need it;
	list<Photo> photos;
	while (getline(infile, line)) {
		auto photo = mLineParser.parse(photoId, line, tagStorage);
		photos.push_back(photo);
		photoId++;
	}
	sort(photos);
	cout << "Photos in list: " << to_string(photos.size()) << endl;

	return photos;
}

void FileParser::sort(list<Photo> &photos) const
{
	photos.sort([](const Photo & a, const Photo & b) { return a.tagCount() > b.tagCount(); });
}
