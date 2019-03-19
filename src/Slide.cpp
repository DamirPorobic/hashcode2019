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

#include "Slide.h"

Slide::Slide(const Photo &photo)
{
	mCountOfPhotos = 1;
	mPhotoIds = new int[1] {photo.id()};
	mTags = photo.tags();
}

Slide::Slide(const Photo &firstPhoto, const Photo &secondPhoto)
{
	mCountOfPhotos = 2;
	mPhotoIds = new int[2] {firstPhoto.id(), secondPhoto.id()};

	mTags = firstPhoto.tags() | secondPhoto.tags();
}

Slide::~Slide()
{
//	delete mPhotoIds;
}

string Slide::toString() const
{
	string output(to_string(mPhotoIds[0]));
	if(mCountOfPhotos > 1) {
		output += " " + to_string(mPhotoIds[1]);
	}
	return output;
}

int Slide::tagCount() const
{
	return static_cast<int>(mTags.count());
}

const tagSet &Slide::tags() const
{
	return mTags;
}
