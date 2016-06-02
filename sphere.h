#pragma once

#include "object.h"
#include "photon.h"

class sphere : public virtual object {
public:
	sphere(tsvector center, mpf_class radius, mpf_class height, tsvector rot) : center(center), radius(radius), height(height), rot(rot){}

	tsvector get_center();
	mpf_class get_radius();
	mpf_class get_height();
	tsvector get_rot();

	std::vector<tsvector> get_points(mpf_class density);

	tsvector get_surface_normal(tsvector point);
	tsvector get_intersection(photon* incident_photon);
	virtual photon* get_redirected_photon(photon* incident_photon) = 0;


#ifdef GRAPHICS
	void draw();
#endif

protected:
	tsvector center;
	mpf_class radius;
	mpf_class height;
	tsvector rot;

	virtual tsvector curve_center_left() = 0;
	virtual tsvector curve_center_right() = 0;
};
