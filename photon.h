#pragma once

#include "light.h"
#include "clock.h"

class photon : public light, public clock {
public:
photon(tsvector origin, tsvector destination, mpf_class wavelength, mpf_class probability) : destination(destination), light(origin, wavelength), clock(0), probability(probability){
		path_valid = true;
		origin_object = NULL;
	}
photon(tsvector origin, object * origin_object, tsvector destination, object * dest_object, mpf_class wavelength, mpf_class probability) : destination(destination), dest_object(dest_object), origin_object(origin_object), light(origin, wavelength), clock(0), probability(probability){
		path_valid = true;
	}

	bool is_valid();

	int calculate(std::vector<object*> objects, mpf_class density, int depth);

	std::vector<photon*> get_paths();

	object * get_origin();
	object * get_dest();

	tsvector get_destination();

#ifdef GRAPHICS
	void draw();
#endif
	
protected:

	bool path_valid;

	tsvector destination;

	object * origin_object;
	object * dest_object;

	mpf_class probability;
};
