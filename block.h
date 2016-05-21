#pragma once

#include "object.h"

class block : public object{
public:
block(tsvector center, tsvector dim, tsvector rot, mpf_class reflectance, mpf_class transmittance, mpf_class lightspeed) : dim(dim), rot(rot), object(center, reflectance, transmittance, lightspeed){}
	
	std::vector<tsvector> get_points(mpf_class density);

	tsvector get_surface_normal(tsvector point);

	bool inside(tsvector point);

	mpf_class get_radius();

#ifdef GRAPHICS
	void draw();
#endif

protected:

	tsvector get_local_normal(tsvector point);
	
	tsvector rot;
	tsvector dim;
};
