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

#include "InterestFactorCalculator.h"

int InterestFactorCalculator::calculateFactor(const Slide &slide1, const Slide &slide2) const
{
    tagSet commonTags;
    tagSet previousTags;
    tagSet nextTags;

    commonTags = slide1.tags() & slide2.tags();
    previousTags = commonTags ^ slide1.tags();
    nextTags = commonTags ^ slide2.tags();

    return getSmallestFactor(previousTags, commonTags, nextTags);
}

int InterestFactorCalculator::getSmallestFactor(const tagSet &previous, const tagSet &common, const tagSet &next) const
{
    return static_cast<int>(min({ previous.count(), common.count(), next.count()}));
}
