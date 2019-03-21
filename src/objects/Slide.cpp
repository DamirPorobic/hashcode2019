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

#include <iterator>
#include "Slide.h"

Slide::Slide(const Photo &photo)
{
	mPhotoIds.insert(photo.id());
	mTags = photo.tags();
}

Slide::Slide(const Photo &firstPhoto, const Photo &secondPhoto)
{
    mPhotoIds.insert(firstPhoto.id());
    mPhotoIds.insert(secondPhoto.id());
	set_union(firstPhoto.tags().begin(), firstPhoto.tags().end(), secondPhoto.tags().begin(), secondPhoto.tags().end(), inserter(mTags, mTags.begin()));
}

string Slide::toString() const
{
	string output;
	for(auto id : mPhotoIds) {
	    output += to_string(id) + " ";
	}
	return output;
}

int Slide::tagCount() const
{
	return static_cast<int>(mTags.size());
}

const set<int> &Slide::tags() const
{
	return mTags;
}
