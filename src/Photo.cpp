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

#include "Photo.h"

Photo::Photo(int id, Orientation orientation, tagSet &tags)
{
	mId = id;
	mOrientation = orientation;
	mTags = tags;
}

int Photo::id() const
{
	return mId;
}

Orientation Photo::orientation() const
{
	return mOrientation;
}

const tagSet& Photo::tags() const
{
	return mTags;
}

int Photo::tagCount() const
{
	return static_cast<int>(tags().count());
}
