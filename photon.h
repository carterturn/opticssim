#pragma once

#include "light.h"
#include "clock.h"

struct object_point{
	object * obj;
	tsvector point;
	vector2d clock;
};

class photon : public light, public clock {
public:
photon(tsvector o, tsvector d, mpf_class wavelength) : light(wavelength), clock(0) {
		origin = new object_point;
		origin->point = o;
		origin->obj = NULL;
		origin->clock = vector2d();

		dest = new object_point;
		dest->point = d;
		dest->obj = NULL;
		dest->clock = vector2d();
		
		path_valid = true;
		prob = 1.0;
	}
photon(object_point * origin, object_point * destination, mpf_class wavelength) : origin(origin), dest(destination), light(wavelength), clock(0) {
		path_valid = true;
		prob = 1.0;
	}

	bool is_valid();

	int calculate(std::vector<object*> objects, mpf_class density, int depth);

	std::vector<photon*> get_paths();

	object_point * get_origin();
	object_point * get_dest();

	mpf_class add_probability(mpf_class probability, bool update_clock);
	mpf_class get_probability();

#ifdef GRAPHICS
	void draw();
#endif
	
protected:

	bool path_valid;

	object_point * origin;
	object_point * dest;

	mpf_class prob;
};
