#include "concavesphere.h"

tsvector concavesphere::curve_center_left(){
	return tsvector(-1.0*radius, 0, 0);
}

tsvector concavesphere::curve_center_right(){
	return curve_center_left() * -1.0;
}
