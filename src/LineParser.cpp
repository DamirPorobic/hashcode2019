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

#include "LineParser.h"

Photo LineParser::parse(int id, string &line, TagStorage &tagStorage) const
{
	istringstream stringStream(line);
	vector<string> allEntries(istream_iterator<string>{stringStream}, istream_iterator<string>());
	Orientation orientation = getOrientation(allEntries[0]);
	set<int> tags;

	for(auto i = 2; i < allEntries.size() ; i++) {
		auto tagId = tagStorage.getId(allEntries[i]);
		tags.insert(tagId);
	}

	return Photo(id, orientation, tags);
}

Orientation LineParser::getOrientation(basic_string<char> &orientationString) const
{ 
	return orientationString == "H" ? Orientation::Horizontal : Orientation::Vertical;
}

