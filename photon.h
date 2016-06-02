#pragma once

#include <vector>
#include "tsvector.h"
#include "object.h"

class photon {
public:
	photon(tsvector origin, tsvector direction) : origin(origin), destination(direction) {}
	tsvector get_origin();
	tsvector get_direction();

	bool is_valid();

	// Determines the path of the photon
	void radiate(std::vector<object*> objects, int depth);

#ifdef GRAPHICS
	// Draws the photon's path
	void draw();
#endif

protected:
	tsvector origin;
	tsvector direction;
};
