#pragma once

#include "object.h"

class block : public object{
public:
block(tsvector center, tsvector dim, tsvector rot, mpf_class reflectance, mpf_class transmittance) : center(center), dim(dim), rot(rot), object(reflectance, transmittance){}
	
	std::vector<tsvector> get_points(mpf_class density);

	tsvector get_reflected(tsvector point);
	tsvector get_transmitted(tsvector point);

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
