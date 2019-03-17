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

	while (!slides.empty()) {
		auto matchingEntry = getMatchingSlide(slides, currentSlide);
		finishedSlides.push_back(*matchingEntry);
		currentSlide = *matchingEntry;
		slides.erase(matchingEntry);
	}
}

list<Slide, std::allocator<Slide>>::iterator Solver::getMatchingSlide(list<Slide> &slides, const Slide &currentSlide) const
{
	auto maxInterestFactor = 0;
	auto iterator = slides.begin();
	auto matchingEntry = iterator;
	while (iterator != slides.end()) {

		if(iterator->tagCount() <= maxInterestFactor) {
			return matchingEntry;
		}

		set<int> commonTags;
		set<int> previousTags;
		set<int> nextTags;
		set_intersection(iterator->tags().begin(), iterator->tags().end(), currentSlide.tags().begin(), currentSlide.tags().end(), inserter(commonTags, commonTags.begin()));
		set_difference(currentSlide.tags().begin(), currentSlide.tags().end(), commonTags.begin(), commonTags.end(), inserter(previousTags, previousTags.begin()));
		set_difference(iterator->tags().begin(), iterator->tags().end(), commonTags.begin(), commonTags.end(), inserter(nextTags, nextTags.begin()));

		auto interestFactor = getInterestFactor(previousTags, commonTags, nextTags);
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

list<Photo, std::allocator<Photo>>::iterator Solver::getMatchingVerticalPhotoWithMaxUnitTags(list<Photo> &photos, const Photo &partnerPhoto) const
{
	auto innerIterator = photos.begin();
	auto maxUniqueTags = innerIterator->tagCount();
	auto matchingEntry = innerIterator;
	while (innerIterator != photos.end()) {
		if(innerIterator->tagCount() + partnerPhoto.tagCount() < maxUniqueTags) {
			return matchingEntry;
		}

		if (innerIterator->orientation() == Orientation::Vertical) {
			set<int> mergedTags;
			set_union(innerIterator->tags().begin(), innerIterator->tags().end(), partnerPhoto.tags().begin(), partnerPhoto.tags().end(), inserter(mergedTags, mergedTags.begin()));

			if (mergedTags.size() > maxUniqueTags) {
				maxUniqueTags = static_cast<int>(mergedTags.size());
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

int Solver::getInterestFactor(const set<int> &previous, const set<int> &common, const set<int> &next) const
{
	return static_cast<int>(min({ previous.size(), common.size(), next.size()}));
}
