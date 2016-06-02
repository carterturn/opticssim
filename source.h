#pragma once

#include <vector>
#include "tsvector.h"
#include "photon.h"

class source {
public:
	source(tsvector origin, double intensity) : origin(origin), intensity(intensity) {}
	tsvector get_origin();
	double get_intensity();

	bool is_valid();

	// Sends out rays (number determined by intensity)
	void radiate(std::vector<object*> objects, int depth);

#ifdef GRAPHICS
	void draw();
#endif

protected:
	tsvector origin;
	double intensity;
};
