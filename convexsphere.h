#pragma once

#include "sphere.h"

class convexsphere : public sphere {
public:
convexsphere(tsvector center, mpf_class radius, mpf_class height, tsvector rot) : sphere(center, radius, height, rot){}
	
protected:
	tsvector get_surface_normal(tsvector point);
	
	tsvector curve_center_left();
	tsvector curve_center_right();
};
