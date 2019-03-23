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

#include "Solver.h"

list<Slide *> Solver::solve(list<Photo> &photos, int tagCount) const
{
	list<Slide*> finishedSlides;
    SlideStorage slideStorage;

	addHorizontalPhotosToSlides(photos, slideStorage, tagCount);
	addVerticalPhotosToSlides(photos, slideStorage, tagCount);

	auto useStorage = tagCount > 1000;
	bringSlidesInOrder(slideStorage, finishedSlides, useStorage);

	return finishedSlides;
}

void Solver::bringSlidesInOrder(SlideStorage &slideStorage, list<Slide *> &finishedSlides, bool useStorage) const
{
	auto allSlides = slideStorage.getAllSlides();

	cout << "Slides to sort: " << to_string(allSlides.size()) << endl;

	auto currentSlide = *allSlides.begin();
	finishSlide(slideStorage, finishedSlides, allSlides, currentSlide, useStorage);

	auto initialSize = allSlides.size();
	auto lastPercent = 0;
	auto slideNumber = 0.0;

	while (!allSlides.empty()) {
		list<Slide *> slidesForLookup;
		if(useStorage) {
			slidesForLookup = slideStorage.getSlidesForTags(currentSlide->tags());
		} else {
			slidesForLookup = allSlides;
		}

		if(slidesForLookup.empty()) {
			currentSlide = *allSlides.begin();
		} else {
			currentSlide = getMatchingSlide(slidesForLookup, currentSlide);
		}

		finishSlide(slideStorage, finishedSlides, allSlides, currentSlide, useStorage);

		slideNumber++;
		auto percent = static_cast<int>(round(slideNumber / initialSize * 100));
		if(percent != lastPercent) {
			cout << to_string(percent) << "%" << endl;
			lastPercent = percent;
		}
	}
}

void Solver::finishSlide(SlideStorage &slideStorage, list<Slide *> &finishedSlides, list<Slide *> &allSlides, Slide *currentSlide, bool useStorage) const
{
	finishedSlides.push_back(currentSlide);
	allSlides.remove(currentSlide);
	if(useStorage) {
		slideStorage.remove(currentSlide);
	}
}

Slide* Solver::getMatchingSlide(list<Slide*> &slides, const Slide *currentSlide) const
{
	auto maxInterestFactor = 0;
	auto iterator = slides.begin();
	auto matchingEntry = iterator;

	while (iterator != slides.end()) {
		if((*iterator)->tagCount() <= maxInterestFactor * 2 + 1) {
			return *matchingEntry;
		}

		auto interestFactor = mInterestFactorCalculator.getInterestFactor(*iterator, currentSlide);
		if (interestFactor > maxInterestFactor) {
			maxInterestFactor = interestFactor;
			matchingEntry = iterator;
		}
		iterator++;
	}

	return *matchingEntry;
}

void Solver::addHorizontalPhotosToSlides(list<Photo> &photos, SlideStorage &slideStorage, int tagCount) const
{
	auto iterator = photos.begin();
	while (iterator != photos.end())
	{
		if(iterator->orientation() == Orientation::Horizontal) {
            slideStorage.add(new Slide(*iterator, tagCount));
			iterator = photos.erase(iterator);
		} else {
			iterator++;
		}
	}
}

void Solver::addVerticalPhotosToSlides(list<Photo> &photos, SlideStorage &slideStorage, int tagCount) const
{
	auto iterator = photos.begin();
	while (iterator != photos.end()) {
		auto currentPhoto = *iterator;
		auto matchingVerticalPhoto = getMatchingVerticalPhoto(photos, currentPhoto);
		slideStorage.add(new Slide(currentPhoto, *matchingVerticalPhoto, tagCount));
		photos.erase(next(matchingVerticalPhoto).base());
		iterator = photos.erase(iterator);
	}
}

photoInListIterator Solver::getMatchingVerticalPhoto(list<Photo> &photos, const Photo &firstPhoto) const
{
	auto iterator = photos.rbegin();
	auto matchingEntry = iterator;
	while (iterator != photos.rend()) {
		if (iterator->orientation() == Orientation::Vertical) {
			set<int> mergedTags;
			set_union(iterator->tags().begin(), iterator->tags().end(), firstPhoto.tags().begin(), firstPhoto.tags().end(), inserter(mergedTags, mergedTags.begin()));

			if (mergedTags.size() == iterator->tagCount() + firstPhoto.tagCount()) {
				return iterator;
			}
		}
		iterator++;
	}

	return matchingEntry;
}
