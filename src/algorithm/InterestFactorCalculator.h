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

#ifndef HASHCODE2019_INTERESTFACTORCALCULATOR_H
#define HASHCODE2019_INTERESTFACTORCALCULATOR_H

#include "src/objects/Slide.h"

class InterestFactorCalculator
{
public:
    int getInterestFactor(const Slide *slide1, const Slide *slide2) const;

private:
    int getSmallestFactor(const set<int> &previous, const set<int> &common, const set<int> &next) const;
};

#endif //HASHCODE2019_INTERESTFACTORCALCULATOR_H
