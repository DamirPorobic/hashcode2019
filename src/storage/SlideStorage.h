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

#ifndef HASHCODE2019_SLIDESTORAGE_H
#define HASHCODE2019_SLIDESTORAGE_H

#include <unordered_map>
#include <list>
#include <set>
#include <iostream>

#include <src/objects/Slide.h>

using namespace std;

class SlideStorage
{
public:
    void add(Slide *slide);
    list<Slide*> getSlidesForTags(const set<int> &tags);
    list<Slide*> getAllSlides();
    void remove(Slide *slide);

private:
    list<Slide*> mAllSlides;
    unordered_map<int,list<Slide*>> mTagIdToSlides;

    void sort(list<Slide*> &slides) const;
};

#endif //HASHCODE2019_SLIDESTORAGE_H
