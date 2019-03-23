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

#ifndef HASHCODE2019_SLIDE_H
#define HASHCODE2019_SLIDE_H

#include <algorithm>
#include <iterator>
#include <boost/dynamic_bitset.hpp>

#include "Photo.h"
#include "Orientation.h"

typedef boost::dynamic_bitset<> tagSet;

using namespace std;

class Slide
{
public:
	explicit Slide(const Photo &photo, int maxTagCount);
	Slide(const Photo &firstPhoto, const Photo &secondPhoto, int maxTagCoun);
	~Slide();
	string toString() const;
	int tagCount() const;
	const tagSet* tags() const;

private:
	set<int> mPhotoIds;
	tagSet *mTags;
	int mCardinality;

	void addTags(const Photo &photo) const;
};

#endif //HASHCODE2019_SLIDE_H
