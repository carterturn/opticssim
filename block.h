#pragma once

#include "object.h"

class block : public object{
public:
block(tsvector center, tsvector dim, tsvector rot, mpf_class reflectance, mpf_class transmittance, mpf_class lightspeed) : center(center), dim(dim), rot(rot), object(reflectance, transmittance, lightspeed){}
	
	std::vector<tsvector> get_points(mpf_class density);

	tsvector get_surface_normal(tsvector point);

	bool inside(tsvector point);

#ifdef GRAPHICS
	void draw();
#endif

protected:
	tsvector center;
	tsvector rot;
	tsvector dim;
};
