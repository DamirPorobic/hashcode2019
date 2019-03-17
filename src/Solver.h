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

#ifndef HASHCODE2019_SOLVER_H
#define HASHCODE2019_SOLVER_H

#include <iostream>
#include <list>
#include <set>

#include "Slide.h"
#include "Photo.h"

class Solver
{
public:
	list<Slide> solve(list<Photo> &photos) const;
	void addHorizontalPhotosToSlides(list<Photo> &photos, list<Slide> &slides) const;
	void addVerticalPhotosToSlides(list<Photo> &photos, list<Slide> &slides) const;
	list<Photo, std::allocator<Photo>>::iterator getMatchingVerticalPhotoWithMaxUnitTags(list<Photo> &photos, const Photo &partnerPhoto) const;
	void sortSlides(list<Slide> &slides) const;
	void bringSlidesInOrder(list<Slide> &slides, list<Slide> &finishedSlides) const;
	list<Slide, std::allocator<Slide>>::iterator getMatchingSlide(list<Slide> &slides, const Slide &currentSlide) const;
	int getInterestFactor(const set<int> &previous, const set<int> &common, const set<int> &next) const;
};

#endif //HASHCODE2019_SOLVER_H
