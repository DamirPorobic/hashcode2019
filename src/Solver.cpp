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

list<Slide> Solver::solve(list<Photo> &photos) const
{
	list<Slide> slides;
	list<Slide> finishedSlides;

	addHorizontalPhotosToSlides(photos, slides);
	addVerticalPhotosToSlides(photos, slides);

	cout << "Slides Created: " << to_string(slides.size()) << endl;

	sortSlides(slides);

	bringSlidesInOrder(slides, finishedSlides);

	return finishedSlides;
}

void Solver::bringSlidesInOrder(list<Slide> &slides, list<Slide> &finishedSlides) const
{
	auto iterator = slides.begin();

	auto currentSlide = *iterator;
	finishedSlides.push_back(currentSlide);
	slides.erase(iterator);
	auto initialSize = slides.size();
	auto lastPercent = 0;
	auto slideNumber = 0.0;

	while (!slides.empty()) {
		auto matchingEntry = getMatchingSlide(slides, currentSlide);
		finishedSlides.push_back(*matchingEntry);
		currentSlide = *matchingEntry;
		slides.erase(matchingEntry);

		slideNumber++;
		auto percent = static_cast<int>(round(slideNumber / initialSize * 100));
		if(percent != lastPercent) {
			cout << to_string(percent) << "%" << endl;
			lastPercent = percent;
		}
	}
}

list<Slide, std::allocator<Slide>>::iterator Solver::getMatchingSlide(list<Slide> &slides, const Slide &currentSlide) const
{
	auto maxInterestFactor = 0;
	auto iterator = slides.begin();
	auto matchingEntry = iterator;
	while (iterator != slides.end()) {

		if(iterator->tagCount() <= maxInterestFactor * 2 + 1) {
			return matchingEntry;
		}

		auto interestFactor = mInterestFactorCalculator.calculateFactor(*iterator, currentSlide);
		if (interestFactor > maxInterestFactor) {
			maxInterestFactor = interestFactor;
			matchingEntry = iterator;
		}
		iterator++;
	}
	return matchingEntry;
}

void Solver::addHorizontalPhotosToSlides(list<Photo> &photos, list<Slide> &slides) const
{
	auto iterator = photos.begin();
	while (iterator != photos.end())
	{
		if(iterator->orientation() == Orientation::Horizontal) {
			auto newSlide = Slide(*iterator);
			slides.push_back(newSlide);
			iterator = photos.erase(iterator);
		} else {
			iterator++;
		}
	}
}

void Solver::addVerticalPhotosToSlides(list<Photo> &photos, list<Slide> &slides) const
{
	auto iterator = photos.begin();
	while (iterator != photos.end()) {
		auto currentPhoto = *iterator;
		auto matchingVerticalPhoto = getMatchingVerticalPhotoWithMaxUnitTags(photos, currentPhoto);

		auto newSlide = Slide(currentPhoto, *matchingVerticalPhoto);
		slides.push_back(newSlide);
		photos.erase(matchingVerticalPhoto);
		iterator = photos.erase(iterator);
	}
}

list<Photo, std::allocator<Photo>>::iterator Solver::getMatchingVerticalPhotoWithMaxUnitTags(list<Photo> &photos, const Photo &firstPhoto) const
{
	auto innerIterator = photos.begin();
	auto maxUniqueTags = innerIterator->tagCount();
	auto matchingEntry = innerIterator;
	while (innerIterator != photos.end()) {
		if(maxUniqueTags >= innerIterator->tagCount() + firstPhoto.tagCount()) {
			return matchingEntry;
		}

		if (innerIterator->orientation() == Orientation::Vertical) {
			tagSet mergedTags;
			mergedTags = innerIterator->tags() | firstPhoto.tags();

			if (mergedTags.count() > maxUniqueTags) {
				maxUniqueTags = static_cast<int>(mergedTags.count());
				matchingEntry = innerIterator;
			}
		}
		innerIterator++;
	}

	return matchingEntry;
}

void Solver::sortSlides(list<Slide> &slides) const
{
	slides.sort([](const Slide & a, const Slide & b) { return a.tagCount() > b.tagCount(); });
}
