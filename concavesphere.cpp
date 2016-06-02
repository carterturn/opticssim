#include "concavesphere.h"
#include <cmath>

tsvector concavesphere::get_surface_normal(tsvector point){
	tsvector local_pos = point - center;
	local_pos.rotate(rot.x.get_d(), rot.y.get_d(), rot.z.get_d());

	if(local_pos.x < 0){
		tsvector radius_vector = local_pos - tsvector(-radius, 0, 0);
		return (radius_vector * (1.0 / radius_vector.abs())).rotate(-rot.x.get_d(), -rot.y.get_d(), -rot.z.get_d()) * -1.0;
	}
	if(local_pos.x > 0){
		tsvector radius_vector = local_pos - tsvector(radius, 0, 0);
		return (radius_vector * (1.0 / radius_vector.abs())).rotate(-rot.x.get_d(), -rot.y.get_d(), -rot.z.get_d()) * -1.0;
	}
	return tsvector(); // If you are the center, you get a zero vector
}

tsvector concavesphere::curve_center_left(){
	return tsvector(-1.0*radius, 0, 0);
}

tsvector concavesphere::curve_center_right(){
	return curve_center_left() * -1.0;
}

