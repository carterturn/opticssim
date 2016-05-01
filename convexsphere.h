#pragma once

#include "sphere.h"

class convexsphere : public sphere {
public:
convexsphere(tsvector center, mpf_class radius, mpf_class height, tsvector rot, mpf_class reflectance, mpf_class transmittance) : sphere(center, radius, height, rot, reflectance, transmittance){}
protected:

	tsvector curve_center_left();
	tsvector curve_center_right();
};
