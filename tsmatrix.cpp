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

#include "tsmatrix.h"
#include <cmath>

#include <iostream>
using namespace std;

tsmatrix::tsmatrix(){
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			d[i][j] = 0;
		}
	}
}

tsmatrix::tsmatrix(mpf_class data[3][3]){
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			d[i][j] = data[i][j];
		}
	}
}

tsmatrix tsmatrix::operator+(const tsmatrix& param){
	tsmatrix result;

	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			result.d[i][j] = d[i][j] + param.d[i][j];
		}
	}
	
	return result;
}

tsmatrix tsmatrix::operator-(const tsmatrix& param){
	tsmatrix result;

	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			result.d[i][j] = d[i][j] - param.d[i][j];
		}
	}
	
	return result;
}

tsmatrix tsmatrix::operator*(const tsmatrix& param){
	tsmatrix result;

	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			result.d[i][j] = d[i][0]*param.d[0][j] +
				d[i][1]*param.d[1][j] +
				d[i][2]*param.d[2][j];
		}
	}
	
	return result;
}

tsvector tsmatrix::operator*(const tsvector& param){
	tsvector result;

	result.x = d[0][0]*param.x + d[0][1]*param.y + d[0][2]*param.z;
	result.y = d[1][0]*param.x + d[1][1]*param.y + d[1][2]*param.z;
	result.z = d[2][0]*param.x + d[2][1]*param.y + d[2][2]*param.z;
	
	return result;
}

tsmatrix tsmatrix::operator*(const int& scalar){
	tsmatrix result;
	
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			result.d[i][j] = scalar*d[i][j];
		}
	}
	
	return result;
}

tsmatrix tsmatrix::operator*(const double& scalar){
	tsmatrix result;
	
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			result.d[i][j] = scalar*d[i][j];
		}
	}
	
	return result;
}

tsmatrix tsmatrix::operator*(const float& scalar){
	tsmatrix result;

	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			result.d[i][j] = scalar*d[i][j];
		}
	}
	
	return result;
}

tsmatrix tsmatrix::operator*(const mpf_class& scalar){
	tsmatrix result;

	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			result.d[i][j] = scalar*d[i][j];
		}
	}
	
	return result;
}

void tsmatrix::print(){
	for(int i = 0; i < 3; i++){
		cout << "[";
		for(int j = 0; j < 3; j++){
			cout << d[i][j].get_d() << " ";
		}
		cout << "\b]\n";
	}
}

mpf_class tsmatrix::det(){
	return (d[0][0]*d[1][1]*d[2][2] +
		d[0][1]*d[1][2]*d[2][0] +
		d[0][2]*d[1][0]*d[2][1]) -
		(d[0][0]*d[1][2]*d[2][1] +
		 d[0][1]*d[1][0]*d[2][2] +
		 d[0][2]*d[1][1]*d[2][0]);
}

mpf_class det(tsmatrix input){
	return input.det();
}
