#pragma once

#include "light.h"
#include "clock.h"

class photon : public light, public clock {
public:
photon(tsvector origin, tsvector destination, mpf_class wavelength) : destination(destination), light(origin, wavelength), clock(0){
		path_valid = true;
	}
	~photon();

	std::vector<photon*> get_paths();
	photon * get_best_path();
	
protected:
	std::vector<photon*> next_bundles;
	bool path_valid;

	tsvector destination;
};
