#pragma once

#include <vector>
#include "tsvector.h"
#include "object.h"

class light {
public:
light(tsvector origin, mpf_class wavelength) : origin(origin), wavelength(wavelength){}

	// Determines the path of the light
	virtual int calculate(std::vector<object*> objects, mpf_class density, int depth) = 0;

	mpf_class get_wavelength(){
		return wavelength;
	}

#ifdef GRAPHICS
	// Draws the light (however the thing wants)
	virtual void draw() = 0;
#endif

protected:
	tsvector origin;
	mpf_class wavelength;
};
