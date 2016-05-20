/*
  Copyright 2016 Carter Turnbaugh

  This file is part of Terca Simulator.

  Terca Simulator is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Terca Simulator is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Terca Simulator.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "tsvector.h"
#include <gmpxx.h>

class tsmatrix{
public:
tsmatrix(mpf_class data[3][3]);
tsmatrix();

	mpf_class d[3][3];

	tsmatrix operator+ (const tsmatrix& param);
	tsmatrix operator- (const tsmatrix& param);
	tsmatrix operator* (const tsmatrix& param);

	tsmatrix operator* (const int& scalar);
	tsmatrix operator* (const double& scalar);
	tsmatrix operator* (const float& scalar);
	tsmatrix operator* (const mpf_class& scalar);
	tsvector operator* (const tsvector& scalar);

	mpf_class det();

	tsmatrix inv();

	void print();
};

mpf_class det(tsmatrix input);

