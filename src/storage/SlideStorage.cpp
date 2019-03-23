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

#include "SlideStorage.h"

void SlideStorage::add(Slide *slide)
{
    mAllSlides.insert(mAllSlides.end(), slide);
    auto pos = slide->tags()->find_first();
    while (pos != tagSet::npos) {
        mTagIdToSlides[pos].push_back(slide);
        pos = slide->tags()->find_next(pos);
    }
}

list<Slide *> SlideStorage::getSlidesForTags(const tagSet *tags)
{
    set<Slide*> slideSet;
    auto pos = tags->find_first();
    while (pos != tagSet::npos) {
        slideSet.insert(mTagIdToSlides[pos].begin(), mTagIdToSlides[pos].end());
        pos = tags->find_next(pos);
    }

    list<Slide*> slideList;
    slideList.insert(slideList.begin(), slideSet.begin(), slideSet.end());
    sort(slideList);

    return slideList;
}

void SlideStorage::sort(list<Slide*> &slides) const
{
    slides.sort([](const Slide *a, const Slide *b) { return a->tagCount() > b->tagCount(); });
}

void SlideStorage::remove(Slide *slide)
{
	auto pos = slide->tags()->find_first();
	while (pos != tagSet::npos) {
		mTagIdToSlides[pos].remove(slide);
		pos = slide->tags()->find_next(pos);
	}
    mAllSlides.remove(slide);
}

list<Slide *> SlideStorage::getAllSlides()
{
    sort(mAllSlides);
    return mAllSlides;
}
