#pragma once

#include <vector>
#include "tsvector.h"
#include "object.h"

class light {
public:
light(mpf_class wavelength) : wavelength(wavelength){}

	mpf_class get_wavelength(){
		return wavelength;
	}

#ifdef GRAPHICS
	// Draws the light (however the thing wants)
	virtual void draw() = 0;
#endif

protected:
	mpf_class wavelength;
};
