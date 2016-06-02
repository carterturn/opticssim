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

#include "tsvector.h"
#include <cmath>
#ifdef GRAPHICS
#include <GL/glut.h>
#endif

// This function rotates a vector. It probably works.
tsvector tsvector::rotate(double tx, double ty, double tz){
	
	tsvector xrot(0.0, 0.0, 0.0);
	//First, x rotation
	xrot.x = x;
	xrot.y = y*cos(tx) - z*sin(tx);
	xrot.z = y*sin(tx) + z*cos(tx);
	
	tsvector yrot(0.0, 0.0, 0.0);
	//Then, y rotation
	yrot.x = xrot.x*cos(ty) + xrot.z*sin(ty);
	yrot.y = xrot.y;
	yrot.z = -1*xrot.x*sin(ty) + xrot.z*cos(ty);
	
	tsvector zrot(0.0, 0.0, 0.0);
	//Finally, z rotation
	zrot.x = yrot.x*cos(tz) - yrot.y*sin(tz);
	zrot.y = yrot.x*sin(tz) + yrot.y*cos(tz);
	zrot.z = yrot.z;
	
	x = zrot.x;
	y = zrot.y;
	z = zrot.z;
	
	return zrot;
}

double tsvector::norm(){
	return sqrt(this * this);
}

tsvector tsvector::normalize(){
	double my_norm = this->norm();
	if (my_norm != 0) {
		return this * (1 / my_norm);
	} else {
		return this;
	}
}

bool tsvector::is_valid(){
	return true;
}

tsvector tsvector::operator+(const tsvector& param){
	tsvector result;
	
	result.x = x + param.x;
	result.y = y + param.y;
	result.z = z + param.z;
	
	return result;
}

tsvector tsvector::operator-(const tsvector& param){
	tsvector result;
	
	result.x = x - param.x;
	result.y = y - param.y;
	result.z = z - param.z;
	
	return result;
}

mpf_class tsvector::operator*(const tsvector& param){
	tsvector result;
	
	result.x = x * param.x;
	result.y = y * param.y;
	result.z = z * param.z;
	
	return result.x + result.y + result.z;
}

tsvector tsvector::operator*(const int& scalar){
	tsvector result;
	
	result.x = x*scalar;
	result.y = y*scalar;
	result.z = z*scalar;
	
	return result;
}

tsvector tsvector::operator*(const double& scalar){
	tsvector result;
	
	result.x = x*scalar;
	result.y = y*scalar;
	result.z = z*scalar;
	
	return result;
}

tsvector tsvector::operator*(const float& scalar){
	tsvector result;
	
	result.x = x*scalar;
	result.y = y*scalar;
	result.z = z*scalar;
	
	return result;
}

tsvector tsvector::operator*(const mpf_class& scalar){
	tsvector result;
	
	result.x = x*scalar;
	result.y = y*scalar;
	result.z = z*scalar;
	
	return result;
}

#ifdef GRAPHICS

void tsvector::draw(tsvector in){
	glVertex3f(in.x.get_d(), in.y.get_d(), in.z.get_d());
}
void tsvector::draw(){
	glVertex3f(x.get_d(), y.get_d(), z.get_d());
}
void glvdraw(tsvector in){
	glVertex3f(in.x.get_d(), in.y.get_d(), in.z.get_d());
}
#endif
