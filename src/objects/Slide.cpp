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

Slide::Slide(const Photo &photo, int maxTagCount)
{
	mPhotoIds.insert(photo.id());
	mTags = new tagSet(static_cast<unsigned long>(maxTagCount));
	addTags(photo);
	mCardinality = static_cast<int>(mTags->count());
}

Slide::Slide(const Photo &firstPhoto, const Photo &secondPhoto, int maxTagCount)
{
    mPhotoIds.insert(firstPhoto.id());
    mPhotoIds.insert(secondPhoto.id());
	mTags = new tagSet(static_cast<unsigned long>(maxTagCount));
	addTags(firstPhoto);
	addTags(secondPhoto);
	mCardinality = static_cast<int>(mTags->count());
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
	return mCardinality;
}

const tagSet *Slide::tags() const
{
	return mTags;
}

void Slide::addTags(const Photo &photo) const
{
	for(auto tag : photo.tags()) {
		mTags->set(static_cast<unsigned long>(tag));
	}
}

Slide::~Slide()
{
	delete mTags;
}
