#pragma once

#include <vector>
#include "material.h"
#include "tsvector.h"


class object : public material{
public:
object(tsvector center, mpf_class reflectance, mpf_class transmittance, mpf_class lightspeed) : center(center), material(reflectance, transmittance, lightspeed){}

	virtual std::vector<tsvector> get_points(mpf_class density) = 0;

	tsvector get_reflected(tsvector point);
	tsvector get_transmitted(tsvector point);

	tsvector get_center();

	virtual tsvector get_surface_normal(tsvector point) = 0;

	virtual tsvector get_intersection(tsvector point, tsvector direction) = 0;

	virtual mpf_class get_radius() = 0;

#ifdef GRAPHICS
	virtual void draw() = 0;
#endif
protected:
	virtual tsvector get_local_normal(tsvector point) = 0;

	tsvector center;
};

struct object_point{
	object * obj;
	tsvector point;
};
