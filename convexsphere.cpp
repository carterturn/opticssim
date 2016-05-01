#include "convexsphere.h"

tsvector convexsphere::curve_center_left(){
	mpf_class height_radius_ratio = (height / 2.0) / radius;
	return tsvector(radius * -cos(asin(height_radius_ratio.get_d())), 0, 0);
}

tsvector convexsphere::curve_center_right(){
	return curve_center_left() * -1.0;
}
