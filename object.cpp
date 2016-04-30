#include "object.h"

tsvector object::get_reflected(tsvector point){
	return get_surface_normal(point) * reflectance;
}

tsvector object::get_transmitted(tsvector point){
	return get_surface_normal(point) * transmittance;
}

