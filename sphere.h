#pragma once

#include "object.h"

class sphere : public object {
public:
sphere(tsvector center, mpf_class radius, mpf_class height, tsvector rot, mpf_class reflectance, mpf_class transmittance, mpf_class lightspeed) : radius(radius), height(height), rot(rot), object(center, reflectance, transmittance, lightspeed){}

	std::vector<tsvector> get_points(mpf_class density);

	tsvector get_surface_normal(tsvector point);

	tsvector get_intersection(tsvector point, tsvector direction);

	mpf_class get_radius();


#ifdef GRAPHICS
	void draw();
#endif

protected:
	virtual tsvector get_local_normal(tsvector point) = 0;

	tsvector rot;

	mpf_class radius;
	mpf_class height;

	virtual tsvector curve_center_left() = 0;
	virtual tsvector curve_center_right() = 0;
};
