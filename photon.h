#pragma once

#include "light.h"

class photon : public light{
public:
photon(tsvector origin) : light(origin);

	std::vector<*photon> get_paths();
	*photon get_best_path();
	
protected:
	std::vector<*photon> next_bundles;
};
