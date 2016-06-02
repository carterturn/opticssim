#pragma once

#include "object.h"


class line : public object{
public:
line(tsvector center, tsvector rot, mpf_class length, mpf_class reflectance, mpf_class transmittance, mpf_class lightspeed): length(length), rot(rot),  object(center, reflectance, transmittance, lightspeed){}

	std::vector<tsvector> get_points(mpf_class density);

	tsvector get_surface_normal(tsvector point);
	tsvector get_local_normal(tsvector point);

	bool inside(tsvector point);

	mpf_class get_radius();

#ifdef GRAPHICS
	void draw();
#endif
	mpf_class length;
	tsvector rot;
};
