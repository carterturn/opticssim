#pragma once

#include "light.h"

class photon : public light{
public:
photon(tsvector origin, tsvector destination, mpf_class wavelength) : destination(destination), light(origin, wavelength){
		clck = clock(0);
		path_valid = true;
	}
	~photon();

	std::vector<*photon> get_paths();
	*photon get_best_path();
	
protected:
	std::vector<*photon> next_bundles;
	bool path_valid;

	tsvector destination;

	clock clck;
};
