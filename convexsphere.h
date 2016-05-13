#pragma once

#include "sphere.h"

class convexsphere : public sphere {
public:
convexsphere(tsvector center, mpf_class radius, mpf_class height, tsvector rot, mpf_class reflectance, mpf_class transmittance, mpf_class lightspeed) : sphere(center, radius, height, rot, reflectance, transmittance, lightspeed){}

	bool inside(tsvector point);
	
protected:
	tsvector get_local_normal(tsvector point);
	
	tsvector curve_center_left();
	tsvector curve_center_right();
};
