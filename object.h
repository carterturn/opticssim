#pragma once

#include <vector>
#include "material.h"
#include "tsvector.h"


class object : public material{
public:
object(mpf_class reflectance, mpf_class transmittance, mpf_class lightspeed) : material(reflectance, transmittance, lightspeed){}

	virtual std::vector<tsvector> get_points(mpf_class density) = 0;

	tsvector get_reflected(tsvector point);
	tsvector get_transmitted(tsvector point);

	virtual tsvector get_surface_normal(tsvector point) = 0;

	virtual bool inside(tsvector point) = 0;

#ifdef GRAPHICS
	virtual void draw() = 0;
#endif
};

struct object_point{
	object * obj;
	tsvector point;
};
