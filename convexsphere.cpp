#include "convexsphere.h"
#include <cmath>

tsvector convexsphere::get_local_normal(tsvector point){
	tsvector local_pos = point - center;
	local_pos.rotate(rot.x.get_d(), rot.y.get_d(), rot.z.get_d());

	if(local_pos.x > 0){
		tsvector radius_vector = local_pos - tsvector(-radius, 0, 0);
		return (radius_vector * (1.0 / radius_vector.abs())).rotate(-rot.x.get_d(), -rot.y.get_d(), -rot.z.get_d());
	}
	if(local_pos.x < 0){
		tsvector radius_vector = local_pos - tsvector(radius, 0, 0);
		return (radius_vector * (1.0 / radius_vector.abs())).rotate(-rot.x.get_d(), -rot.y.get_d(), -rot.z.get_d());
	}
	return tsvector(); // If you are the center, you get a zero vector
}

tsvector convexsphere::curve_center_left(){
	mpf_class height_radius_ratio = (height / 2.0) / radius;
	return tsvector(radius * -cos(asin(height_radius_ratio.get_d())), 0, 0);
}

tsvector convexsphere::curve_center_right(){
	return curve_center_left() * -1.0;
}

bool convexsphere::inside(tsvector point){
	tsvector local_pos = point - center;
	local_pos.rotate(rot.x.get_d(), rot.y.get_d(), rot.z.get_d());

	return (abs(local_pos - curve_center_left()) < radius) &&
		(abs(local_pos - curve_center_right()) < radius);
}

mpf_class convexsphere::get_radius(){
	return radius;
}
