#pragma once

#include "light.h"
#include "clock.h"

class photon : public light, public clock {
public:
photon(tsvector origin, tsvector destination, mpf_class wavelength) : destination(destination), light(origin, wavelength), clock(0){
		next_bundles = std::vector<photon*>();
		path_valid = true;
	}
	~photon();

	bool is_valid();

	int calculate(std::vector<object*> objects, mpf_class density, int depth);

	std::vector<photon*> get_paths();
	photon * get_best_path();

#ifdef GRAPHICS
	void draw();
#endif
	
protected:
	std::vector<photon*> next_bundles;
	bool path_valid;

	tsvector destination;
};
