#pragma once

#include <vector>
#include "material.h"
#include "tsvector.h"

class object : public material{
public:
object(mpf_class reflectance, mpf_class transmittance) : material(reflectance, transmittance){}

	virtual std::vector<tsvector> get_points(mpf_class density) = 0;

	virtual tsvector get_reflected(tsvector point) = 0;
	virtual tsvector get_transmitted(tsvector point) = 0;

	virtual tsvector get_surface_normal(tsvector point) = 0;

	virtual bool inside(tsvector point) = 0;

#ifdef GRAPHICS
	virtual void draw() = 0;
#endif
};
