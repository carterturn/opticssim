#pragma once

#include "sphere.h"

class concavesphere : public sphere {
public:
concavesphere(tsvector center, mpf_class radius, mpf_class height, tsvector rot, mpf_class reflectance, mpf_class transmittance) : sphere(center, radius, height, rot, reflectance, transmittance){}

	tsvector get_surface_normal(tsvector point);

	bool inside(tsvector point);
	
protected:

	tsvector curve_center_left();
	tsvector curve_center_right();
};
