#pragma once

#include <vector>
#include <gmpxx.h>
#include "tsvector.h"


class object {
public:
	object() : {}

	virtual std::vector<tsvector> get_points(mpf_class density) = 0;

	virtual tsvector get_surface_normal(tsvector point) = 0;

	virtual tsvector get_intersection(photon incident_photon) = 0;

	virtual photon get_redirected_photon() = 0;

#ifdef GRAPHICS
	virtual void draw() = 0;
#endif
};

struct object_point{
	object * obj;
	tsvector point;
};
