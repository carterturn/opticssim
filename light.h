#pragma once

#include <vector>
#include "tsvector.h"
#include "object.h"

class light {
public:
light(tsvector origin, mpf_class wavelength) : origin(origin), wavelength(wavelength){}

	// Returns true while the light is in allowed space
	virtual bool is_valid() = 0;

	// Determines the path of the light
	virtual int calculate(std::vector<object*> objects) = 0;

#ifdef GRAPHICS
	// Draws the light (however the thing wants)
	virtual void draw() = 0;
#endif

protected:
	tsvector origin;
	mpf_class wavelength;
};
