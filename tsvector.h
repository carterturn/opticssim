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

#include <gmpxx.h>

class tsvector{
public:
	tsvector(mpf_class glvx, mpf_class glvy, mpf_class glvz){
		x = glvx;
		y = glvy;
		z = glvz;
	}
	tsvector(){
		x = mpf_class(0.0);
		y = mpf_class(0.0);
		z = mpf_class(0.0);
	}
	
	mpf_class x;
	mpf_class y;
	mpf_class z;
	
	tsvector rotate(double tx, double ty, double tz);
	double norm();
	tsvector normalize();
	bool is_valid();
	
	tsvector operator+ (const tsvector& param);
	tsvector operator- (const tsvector& param);
	mpf_class operator* (const tsvector& param);

	tsvector operator* (const int& scalar);
	tsvector operator* (const double& scalar);
	tsvector operator* (const float& scalar);
	tsvector operator* (const mpf_class& scalar);

	mpf_class abs();

#ifdef GRAPHICS
	void draw(tsvector in);
	void draw();
#endif
};

mpf_class abs(tsvector input);

#ifdef GRAPHICS
void gldraw(tsvector in);
#endif
