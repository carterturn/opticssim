#pragma once

#include "object.h"

class sphere : public object {
public:
sphere(tsvector center, mpf_class radius, mpf_class height, tsvector rot, mpf_class reflectance, mpf_class transmittance, mpf_class lightspeed) : center(center), radius(radius), height(height), rot(rot), object(reflectance, transmittance, lightspeed){}

	std::vector<tsvector> get_points(mpf_class density);

	virtual tsvector get_surface_normal(tsvector point) = 0;

	virtual bool inside(tsvector point) = 0;

#ifdef GRAPHICS
	void draw();
#endif

protected:
	tsvector center;
	tsvector rot;

	mpf_class radius;
	mpf_class height;

	virtual tsvector curve_center_left() = 0;
	virtual tsvector curve_center_right() = 0;
};
