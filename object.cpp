#include "object.h"

tsvector object::get_reflected(tsvector point){
	return get_local_normal(point) * reflectance;
}

tsvector object::get_transmitted(tsvector point){
	return get_local_normal(point) * (-1.0 * transmittance);
}

tsvector object::get_center(){
	return center;
}
