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

int InterestFactorCalculator::getInterestFactor(const Slide &slide1, const Slide &slide2) const
{
    set<int> commonTags;
    set<int> previousTags;
    set<int> nextTags;
    set_intersection(slide2.tags().begin(), slide2.tags().end(), slide1.tags().begin(), slide1.tags().end(), inserter(commonTags, commonTags.begin()));
    set_difference(slide1.tags().begin(), slide1.tags().end(), commonTags.begin(), commonTags.end(), inserter(previousTags, previousTags.begin()));
    set_difference(slide2.tags().begin(), slide2.tags().end(), commonTags.begin(), commonTags.end(), inserter(nextTags, nextTags.begin()));

    return getSmallestFactor(previousTags, commonTags, nextTags);
}

int InterestFactorCalculator::getSmallestFactor(const set<int> &previous, const set<int> &common, const set<int> &next) const
{
    return static_cast<int>(min({ previous.size(), common.size(), next.size()}));
}
