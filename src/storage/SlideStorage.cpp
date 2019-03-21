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
    for(auto tag : slide->tags()) {
        mTagIdToSlides[tag].push_back(slide);
    }
}

list<Slide *> SlideStorage::getSlidesForTags(const set<int> &tags)
{
    set<Slide*> slideSet;
    for(auto tag : tags) {
        slideSet.insert(mTagIdToSlides[tag].begin(), mTagIdToSlides[tag].end());
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
    for(auto tag : slide->tags()) {
        mTagIdToSlides[tag].remove(slide);
    }
    mAllSlides.remove(slide);
}

list<Slide *> SlideStorage::getAllSlides()
{
    sort(mAllSlides);
    return mAllSlides;
}
