#pragma once

#include "object.h"

class sphere : public object {
public:
	sphere(tsvector center, mpf_class radius, mpf_class height, tsvector rot) : radius(radius), height(height), rot(rot){}

	std::vector<tsvector> get_points(mpf_class density);

	tsvector get_surface_normal(tsvector point);

	tsvector get_intersection(tsvector point, tsvector direction);

	mpf_class get_radius();

	virtual photon get_redirected_photon() = 0;


#ifdef GRAPHICS
	void draw();
#endif

protected:
	tsvector rot;

	mpf_class radius;
	mpf_class height;

	virtual tsvector curve_center_left() = 0;
	virtual tsvector curve_center_right() = 0;
};
