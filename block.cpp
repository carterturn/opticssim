#include "block.h"

#ifdef GRAPHICS
#include <GL/gl.h>
#endif

using namespace std;

tsvector block::get_surface_normal(tsvector point){
	return get_local_normal(point) + point;
}

tsvector block::get_local_normal(tsvector point){
	tsvector local_pos = point - center;
	local_pos.rotate(rot.x.get_d(), rot.y.get_d(), rot.z.get_d());
	local_pos.x = local_pos.x / dim.x;
	local_pos.y = local_pos.y / dim.y;
	local_pos.z = local_pos.z / dim.z;

	if(abs(local_pos.x) > abs(local_pos.z)){
		if(abs(local_pos.x) > abs(local_pos.y)){
			if(local_pos.x > 0.25) return tsvector(1, 0, 0);
			if(local_pos.x < -0.25) return tsvector(-1, 0, 0);
		}
		if(abs(local_pos.y) > abs(local_pos.z)){
			if(local_pos.y > 0.25) return tsvector(0, 1, 0);
			if(local_pos.y < -0.25) return tsvector(0, -1, 0);
		}
	}
	if(local_pos.z > 0.25) return tsvector(0, 0, 1);
	if(local_pos.z < -0.25) return tsvector(0, 0, -1);
	return tsvector(); // If you are the center, you get a zero vector
}

mpf_class block::get_radius(){
	return (dim * (1.0/2.0)).abs();
}

#ifdef GRAPHICS
void block::draw(){
	glBegin(GL_POINTS);

	mpf_class spacing = min(min(dim.x, dim.y), dim.z);
	vector<tsvector> points = get_points(spacing);
	for(int i = 0; i < points.size(); i++){
		points[i].draw();
	}
	
	glEnd();
}
#endif

/**
   This function is from Terca Simulator tscube.cpp

   Copyright 2016 Carter Turnbaugh
   Copyright 2016 Carter Turnbaugh

   This function was part of Terca Simulator.

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
bool block::inside(tsvector point){
	tsvector local_pos = point - center;
	local_pos.rotate(rot.x.get_d(), rot.y.get_d(), rot.z.get_d());
	return (local_pos.x >= -0.5*dim.x && local_pos.x <= 0.5*dim.x) &&
		(local_pos.y >= -0.5*dim.y && local_pos.y <= 0.5*dim.y) &&
		(local_pos.z >= -0.5*dim.z && local_pos.z <= 0.5*dim.z);
}

/**
   This function is from Terca Simulator tscube.cpp

   Copyright 2016 Carter Turnbaugh
   Copyright 2016 Carter Turnbaugh

   This function was part of Terca Simulator.

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
vector<tsvector> block::get_points(mpf_class spacing){
	vector<tsvector> points = vector<tsvector>();

	tsvector bound = dim*0.5;
	tsvector neg_bound = dim*-0.5;

 	for(mpf_class i = neg_bound.x; i < bound.x + spacing; i += spacing){
		if(i > bound.x) i = bound.x;
		for(mpf_class j = neg_bound.y; j < bound.y + spacing; j += spacing){
			if(j > bound.y) j = bound.y;
			tsvector point_vector = tsvector(i, j, dim.z*0.5);
			point_vector.rotate(rot.x.get_d(), rot.y.get_d(), rot.z.get_d());
			points.push_back(center + point_vector);
			point_vector = tsvector(i, j, dim.z*-0.5);
			point_vector.rotate(rot.x.get_d(), rot.y.get_d(), rot.z.get_d());
			points.push_back(center + point_vector);
		}
	}
	for(mpf_class i = neg_bound.x + spacing; i < bound.x; i += spacing){
		for(mpf_class j = neg_bound.z; j < bound.z + spacing; j += spacing){
			if(j > bound.z) j = bound.z;
			tsvector point_vector = tsvector(i, dim.y*0.5, j);
			point_vector.rotate(rot.x.get_d(), rot.y.get_d(), rot.z.get_d());
			points.push_back(center + point_vector);
			point_vector = tsvector(i, dim.y*-0.5, j);
			point_vector.rotate(rot.x.get_d(), rot.y.get_d(), rot.z.get_d());
			points.push_back(center + point_vector);
		}
	}
	for(mpf_class i = neg_bound.y + spacing; i < bound.y; i += spacing){
		for(mpf_class j = neg_bound.z + spacing; j < bound.z; j += spacing){
			tsvector point_vector = tsvector(dim.x*0.5, i, j);
			point_vector.rotate(rot.x.get_d(), rot.y.get_d(), rot.z.get_d());
			points.push_back(center + point_vector);
			point_vector = tsvector(dim.x*-0.5, i, j);
			point_vector.rotate(rot.x.get_d(), rot.y.get_d(), rot.z.get_d());
			points.push_back(center + point_vector);
		}
	}
	
	return points;

}
