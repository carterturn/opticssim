#pragma once

#include "light.h"
#include "clock.h"

class photon : public light, public clock {
public:
photon(tsvector origin, tsvector destination, mpf_class wavelength) : destination(destination), light(origin, wavelength), clock(0){
		next_nodes = std::vector<photon*>();
		next_depth = std::vector<int>();
		path_valid = true;
		origin_object = NULL;
	}
photon(tsvector origin, object * origin_object, tsvector destination, mpf_class wavelength) : destination(destination), origin_object(origin_object), light(origin, wavelength), clock(0){
		next_nodes = std::vector<photon*>();
		path_valid = true;
	}
	~photon();

	bool is_valid();

	int calculate(std::vector<object*> objects, mpf_class density, int depth);

	std::vector<photon*> get_paths();

	object * get_origin();

	int propagate_probability(mpf_class probability);

#ifdef GRAPHICS
	void draw();
#endif
	
protected:

	std::vector<photon*> next_nodes;
	std::vector<int> next_depth;
	bool path_valid;

	tsvector destination;

	object * origin_object;

	mpf_class probability;
};
